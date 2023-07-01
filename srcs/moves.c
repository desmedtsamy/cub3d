/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:16:51 by samy              #+#    #+#             */
/*   Updated: 2023/07/01 14:42:10 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move(float pos_x, float pos_y, t_game *game)
{
	char	new_pos;

	new_pos = game->map[(int)pos_y][(int)pos_x];
	if (is_accesible(new_pos))
	{
		game->player.pos.y = pos_y;
		game->player.pos.x = pos_x;
	}
}
