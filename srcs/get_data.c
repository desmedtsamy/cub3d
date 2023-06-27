/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:06:35 by samy              #+#    #+#             */
/*   Updated: 2023/06/27 17:41:20 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_color_value(int *color, char *str, t_game *game)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split)
		error("Malloc error", game);
	if (ft_nb_split(split) != 3)
		error("Wrong color format", game);
	if (ft_strlen(split[0]) > 3 || ft_strlen(split[1]) > 3
		|| ft_strlen(split[2]) > 3)
		error("Wrong color format", game);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255
		|| b < 0 || b > 255)
		error("Wrong color value", game);
	ft_free_split(split);
	*color = (r << 16 | g << 8 | b);
}

static void	get_color(char *pos, char *color, t_game *game)
{
	if (color[ft_strlen(color) - 1] == '\n')
		color[ft_strlen(color) - 1] = '\0';
	if (ft_strcmp(pos, "F") == 0)
		get_color_value(&game->floor_color, color, game);
	else if (ft_strcmp(pos, "C") == 0)
		get_color_value(&game->ceiling_color, color, game);
	else
		error("Wrong color", game);
}

static void	get_map(char *line, t_game *game)
{
	t_list	*new;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	new = ft_lstnew(ft_strdup(line));
	if (!new)
		error("Malloc error", game);
	ft_lstadd_back(&game->map_list, new);
}

static int	check_line(char *line, char *name, char *value, t_game *game)
{
	if (ft_strcmp(name, "NO") == 0 || ft_strcmp(name, "SO") == 0)
		get_texture(name, value, game);
	else if (ft_strcmp(name, "WE") == 0 || ft_strcmp(name, "EA") == 0)
		get_texture(name, value, game);
	else if (ft_strcmp(name, "F") == 0 || ft_strcmp(name, "C") == 0)
		get_color(name, value, game);
	else if (!ft_strncmp(name, "1", 1))
	{
		get_map(line, game);
		return (42);
	}
	else
		return (1);
	return (0);
}

void	get_data(int fd, t_game *game)
{
	char	*line;
	char	**split;
	int		result;
	int		is_map;

	is_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		if (!split)
			error("Malloc error", NULL);
		if (split[0] && !ft_isempty(split[0]))
		{
			result = check_line(line, split[0], split[1], game);
			if (result == 42)
				is_map = 1;
			if ((is_map && result != 42) || result == 1)
				error("Error\ninvalid data in cub file", game);
		}
		free(line);
		ft_free_split(split);
		line = get_next_line(fd);
	}
	free(line);
}
