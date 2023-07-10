/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:13:03 by samy              #+#    #+#             */
/*   Updated: 2023/07/10 11:36:35 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_width(t_game *game)
{
	t_list	*row;
	int		size;

	row = game->map_list;
	while (row)
	{
		size = ft_strlen((char *)row->content);
		if (size > game->map_width)
			game->map_width = size;
		row = row->next;
	}
}

void	create_map(t_game *game)
{
	t_list	*row;
	int		index;
	char	*c;
	int		i;

	index = 0;
	game->map_height = ft_lstsize(game->map_list);
	game->map = ft_calloc(sizeof(char *), game->map_height);
	if (!game->map)
		error_parsing("Malloc error", game);
	set_width(game);
	row = game->map_list;
	while (row)
	{
		i = -1;
		game->map[index] = ft_calloc(sizeof(char), game->map_width);
		c = (char *)row->content;
		while (++i < game->map_width && c[i])
			game->map[index][i] = c[i];
		game->map[index++][i] = '\0';
		row = row->next;
	}
	game->map[index] = NULL;
	ft_lstclear(&game->map_list, free);
	game->map_list = NULL;
}

static int	is_valid_pos(int row, int col, char **map, t_game *g)
{
	char	up;
	char	down;
	char	left;
	char	right;

	if (row - 1 < 0)
		return (0);
	up = map[row - 1][col];
	if (row + 1 >= g->map_height)
		return (0);
	down = map[row + 1][col];
	left = map[row][col - 1];
	right = map[row][col + 1];
	if (!up || (up && (up != '1' && !is_accesible(row - 1, col, g))))
		return (0);
	if (!down || (down && (down != '1' && !is_accesible(row + 1, col, g))))
		return (0);
	if (!left || (left && (left != '1' && !is_accesible(row, col - 1, g))))
		return (0);
	if (!right || (right && (right != '1' && !is_accesible(row, col + 1, g))))
		return (0);
	return (1);
}

int	is_valid_map(t_game *game)
{
	int	row;
	int	col;
	int	start_pos;

	row = -1;
	start_pos = 0;
	while (game->map[++row])
	{
		col = -1;
		while (game->map[row][++col])
		{
			if (!is_valid_elem(row, col, game))
				error("invalid element", game);
			if (is_start_pos(game->map[row][col]))
				if (!set_start_pos(row, col, &start_pos, game))
					error("multiple start position", game);
			if (game->map[row][col] == '0' || is_start_pos(game->map[row][col]))
				if (!is_valid_pos(row, col, game->map, game))
					error("bad map", game);
		}
	}
	if (!start_pos)
		error("No start position", game);
	return (1);
}
