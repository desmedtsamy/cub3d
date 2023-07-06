/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:16:51 by samy              #+#    #+#             */
/*   Updated: 2023/07/06 17:55:18 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	slide(t_game *game, int new_x, int new_y, int up_or_down)
{
	int		curr_x;
	int		curr_y;
	double	speed;

	curr_x = (int)game->player.pos.x;
	curr_y = (int)game->player.pos.y;
	speed = (double)SLIDE_SPEED;
	if (is_accesible(game->map[new_y][curr_x]))
		game->player.pos.y += (speed * up_or_down) * game->player.dir.y;
	if (is_accesible(game->map[curr_y][new_x]))
		game->player.pos.x += (speed * up_or_down) * game->player.dir.x;
}

void	move(t_game *game, int up_or_down)
{
	int		new_x;
	int		new_y;
	double	speed;

	speed = (double)MOVE_SPEED;
	new_x = (int)(game->player.pos.x + (speed * up_or_down) * game->player.dir.x);
	new_y = (int)(game->player.pos.y + (speed * up_or_down) * game->player.dir.y);
	if (is_accesible(game->map[new_y][new_x]))
	{
		game->player.pos.y += (speed * up_or_down) * game->player.dir.y;
		game->player.pos.x += (speed * up_or_down) * game->player.dir.x;
	}
	else
		slide(game, new_x, new_y, up_or_down);
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
