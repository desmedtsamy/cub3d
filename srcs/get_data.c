/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:06:35 by samy              #+#    #+#             */
/*   Updated: 2023/07/05 20:29:48 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_color_value(int fd, int *color, char *str, t_game *game)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split)
		error("Malloc error", game);
	if (ft_nb_split(split) != 3)
		error_parsing(fd, game);
	if (ft_strlen(split[0]) > 3 || ft_strlen(split[1]) > 3
		|| ft_strlen(split[2]) > 3)
		error_parsing(fd, game);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_parsing(fd, game);
	ft_free_split(split);
	*color = (r << 16 | g << 8 | b);
}

static void	get_color(int fd, char *pos, char *color, t_game *game)
{
	if (color[ft_strlen(color) - 1] == '\n')
		color[ft_strlen(color) - 1] = '\0';
	if (ft_strcmp(pos, "F") == 0)
		get_color_value(fd, &game->floor_color, color, game);
	else if (ft_strcmp(pos, "C") == 0)
		get_color_value(fd, &game->ceiling_color, color, game);
	else
		error_parsing(fd, game);
}

static int	get_map(char *line, t_game *game)
{
	t_list	*new;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	new = ft_lstnew(ft_strdup(line));
	if (!new)
		error("Malloc error", game);
	ft_lstadd_back(&game->map_list, new);
	return (42);
}

static int	check_line(int fd, t_data *d, t_game *game)
{
	if ((ft_strcmp(d->name, "NO") == 0 || ft_strcmp(d->name, "SO") == 0
			|| ft_strcmp(d->name, "WE") == 0 || ft_strcmp(d->name, "EA") == 0)
		&& d->textures-- > 0)
	{
		if (d->colors == 2 || d->colors == 0)
			get_texture(d->name, d->value, game);
		else
			error_parsing(fd, game);
	}
	else if ((ft_strcmp(d->name, "F") == 0 || ft_strcmp(d->name, "C") == 0)
		&& d->colors-- > 0)
	{
		if (d->textures == 4 || d->textures == 0)
			get_color(fd, d->name, d->value, game);
		else
			error_parsing(fd, game);
	}
	else if (!ft_strncmp(d->name, "1", 1))
	{
		d->map = 1;
		return (get_map(d->line, game));
	}
	else
		return (1);
	return (0);
}

void	get_data(int fd, t_game *game)
{
	char	**split;
	int		result;
	t_data	d;

	init_data(fd, &d);
	while (d.line)
	{
		split = ft_split(d.line, ' ');
		if (!split)
			error("Malloc error", NULL);
		d.name = split[0];
		d.value = split[1];
		if (d.name && !ft_isempty(d.name))
		{
			result = check_line(fd, &d, game);
			if ((d.map && result != 42) || result == 1)
				error_parsing(fd, game);
		}
		free(d.line);
		ft_free_split(split);
		d.line = get_next_line(fd);
	}
	free(d.line);
	if (d.textures || d.colors || !d.map)
		error_parsing(fd, game);
}
