/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:55:00 by samy              #+#    #+#             */
/*   Updated: 2023/07/06 22:50:59 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_start_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_accesible(int y, int x, t_game *game)
{
	char	c;

	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	c = game->map[y][x];
	if (c == '0' || is_start_pos(c))
		return (1);
	return (0);
}

int	is_valid_elem(int y, int x, t_game *game)
{
	char	c;

	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	c = game->map[y][x];
	if (c == '1' || c == ' ' || is_accesible(y, x, game))
		return (1);
	return (0);
}
