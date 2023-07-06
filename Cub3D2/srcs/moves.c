/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:16:51 by samy              #+#    #+#             */
/*   Updated: 2023/07/05 14:05:02 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move(t_game *game, int up_or_down)
{
	int		new_x;
	int		new_y;

	if (up_or_down == 1)
	{
		new_x = (int)(game->player.pos.x + 0.5 * game->player.dir.x);
		new_y = (int)(game->player.pos.y + 0.5 * game->player.dir.y);
		if (is_accesible(game->map[new_y][new_x]))
		{
			game->player.pos.y += 0.5 * game->player.dir.y;
			game->player.pos.x += 0.5 * game->player.dir.x;
		}
	}
	if (up_or_down == -1)
	{
		new_x = (int)(game->player.pos.x - 0.5 * game->player.dir.x);
		new_y = (int)(game->player.pos.y - 0.5 * game->player.dir.y);
		if (is_accesible(game->map[new_y][new_x]))
		{
			game->player.pos.y -= 0.5 * game->player.dir.y;
			game->player.pos.x -= 0.5 * game->player.dir.x;
		}
	}
	// printf("pos x %f pos y %f\n", game->player.pos.x, game->player.pos.y);
}

void	rotate(t_game *game, int left_or_right)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	if (left_or_right == -1)
	{
		game->player.dir.x = game->player.dir.x * cos(-0.2) - game->player.dir.y
			* sin(-0.2);
		game->player.dir.y = old_dir_x * sin(-0.2) + game->player.dir.y
			* cos(-0.2);
		game->player.plane.x = game->player.plane.x * cos(-0.2)
			- game->player.plane.y * sin(-0.2);
		game->player.plane.y = old_plane_x * sin(-0.2) + game->player.plane.y
			* cos(-0.2);
	}
	if (left_or_right == 1)
	{
		game->player.dir.x = game->player.dir.x * cos(0.2) - game->player.dir.y
			* sin(0.2);
		game->player.dir.y = old_dir_x * sin(0.2) + game->player.dir.y * cos(0.2);
		game->player.plane.x = game->player.plane.x * cos(0.2)
			- game->player.plane.y * sin(0.2);
		game->player.plane.y = old_plane_x * sin(0.2) + game->player.plane.y
			* cos(0.2);
	}
	// printf("dir x %f dir y %f\n", game->player.dir.x, game->player.dir.y);
}
