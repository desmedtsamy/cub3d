/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:13:03 by samy              #+#    #+#             */
/*   Updated: 2023/06/30 14:58:18 by hgeissle         ###   ########.fr       */
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
	game->map = ft_calloc(sizeof(char *), game->map_height + 1);
	if (!game->map)
		error("Malloc error", game);
	set_width(game);
	row = game->map_list;
	while (row)
	{
		i = -1;
		game->map[index] = ft_calloc(sizeof(char), game->map_width + 1);
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

static int	is_valid_pos(int row, int col, char **map)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = map[row - 1][col];
	down = map[row + 1][col];
	left = map[row][col - 1];
	right = map[row][col + 1];
	if (!up || (up != '1' && !is_accesible(up)))
		return (0);
	if (!down || (down != '1' && !is_accesible(down)))
		return (0);
	if (!left || (left != '1' && !is_accesible(left)))
		return (0);
	if (!right || (right != '1' && !is_accesible(right)))
		return (0);
	return (1);
}

static int	set_start_pos(int row, int col, int *start_pos, t_game *game)
{
	if (*start_pos)
		return (0);
	*start_pos = 1;
	game->player.pos.x = col;
	game->player.pos.y = row;
	game->player.start_pos.x = col;
	game->player.start_pos.y = row;
	if (game->map[row][col] == 'E')
		game->player.orientation = 0.0 * (M_PI / 180.0);
	if (game->map[row][col] == 'N')
		game->player.orientation = 90.0 * (M_PI / 180.0);
	if (game->map[row][col] == 'W')
		game->player.orientation = 180.0 * (M_PI / 180.0);
	if (game->map[row][col] == 'S')
		game->player.orientation = 270.0 * (M_PI / 180.0);
	return (1);
}

int	is_valid_map(t_game *game)
{
	int	row;
	int	col;
	int	start_pos;

	row = 0;
	start_pos = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (!is_valid_elem(game->map[row][col]))
				error("Invalid element", game);
			if (is_start_pos(game->map[row][col]))
				if (!set_start_pos(row, col, &start_pos, game))
					error("multiple start position", game);
			if (game->map[row][col] == '0' || is_start_pos(game->map[row][col]))
				if (!is_valid_pos(row, col, game->map))
					error("map wasn't surrounded by walls", game);
			col++;
		}
		row++;
	}
	return (1);
}
