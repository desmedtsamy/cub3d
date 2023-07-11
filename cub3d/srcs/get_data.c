/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:06:35 by samy              #+#    #+#             */
/*   Updated: 2023/07/11 12:56:24 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_color(char *pos, char *color, t_game *game)
{
	if (ft_strcmp(pos, "F") == 0)
		get_color_value(&game->floor_color, color, game);
	else if (ft_strcmp(pos, "C") == 0)
		get_color_value(&game->ceiling_color, color, game);
	else
		error_parsing("bad color name", game);
}

static int	get_map(char *line, t_game *game)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup(line));
	if (!new)
		error_parsing("Malloc error", game);
	ft_lstadd_back(&game->map_list, new);
	return (42);
}

static int	check_line(t_data *d, t_game *game)
{
	if (!d->name || *d->name == '1' || *d->name == '0')
	{
		d->map = 1;
		return (get_map(d->line, game));
	}
	else if (is_dir(d->name) && d->textures-- > 0)
		get_texture(d->name, d->value, game);
	else if ((!ft_strcmp(d->name, "F") || !ft_strcmp(d->name, "C"))
		&& d->colors-- > 0)
		get_color(d->name, d->value, game);
	else
		error_parsing("unknown data inside cub file", game);
	return (0);
}

static int	split_data(t_data *d, t_game *game)
{
	char	*tmp;

	d->line = get_next_line(game->fd);
	if (!d->line)
		return (0);
	d->line[ft_strlen(d->line) - 1] = '\0';
	if (ft_is_empty(d->line))
		return (1);
	d->name = ft_strtrim(d->line, " ");
	if (!d->name)
		error_parsing("Malloc error", game);
	if (*d->name == '1' || *d->name == '0')
		return (1);
	tmp = ft_strchr(d->name, ' ');
	if (tmp)
	{
		*tmp = '\0';
		d->value = ft_strtrim(tmp + 1, " ");
		if (!d->value)
			error_parsing("Malloc error", game);
	}
	return (1);
}

void	get_data(t_game *game)
{
	int		result;
	t_data	d;

	init_data(&d);
	while (split_data(&d, game))
	{
		if ((d.name && !ft_is_empty(d.name)) || d.map)
		{
			result = check_line(&d, game);
			if ((d.map && result != 42))
				error_parsing("bad data inside map", game);
		}
		free(d.name);
		d.name = NULL;
		d.value = NULL;
		free(d.line);
	}
	free(d.line);
	if (d.textures || d.colors || !d.map)
		error_parsing("missing elements in cub file", game);
}
