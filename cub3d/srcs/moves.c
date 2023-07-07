/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:16:51 by samy              #+#    #+#             */
/*   Updated: 2023/07/07 10:45:43 by hgeissle         ###   ########.fr       */
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
	if (is_accesible(new_y, curr_x, game))
		game->player.pos.y += (speed * up_or_down) * game->player.dir.y;
	else if (is_accesible(curr_y, new_x, game))
		game->player.pos.x += (speed * up_or_down) * game->player.dir.x;
}

void	move_forward(t_game *game, int x)
{
	double	speed;
	int		new_x;
	int		new_y;

	speed = (double)MOVE_SPEED;
	new_x = (int)(game->player.pos.x + (speed * x) * game->player.dir.x);
	new_y = (int)(game->player.pos.y + (speed * x) * game->player.dir.y);
	if (is_accesible(new_y, new_x, game))
	{
		game->player.pos.x += (speed * x) * game->player.dir.x;
		game->player.pos.y += (speed * x) * game->player.dir.y;
	}
	else
		slide(game, new_x, new_y, x);
}

void	move_sideways(t_game *game, int y)
{
	double	speed;
	int		new_x;
	int		new_y;

	speed = (double)SIDE_SPEED;
	new_x = (int)(game->player.pos.x + (speed * y) * game->player.dir.y);
	new_y = (int)(game->player.pos.y - (speed * y) * game->player.dir.x);
	if (is_accesible(new_y, new_x, game))
	{
		game->player.pos.x += (speed * y) * game->player.dir.y;
		game->player.pos.y -= (speed * y) * game->player.dir.x;
	}
	else
		slide(game, new_x, new_y, y);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	speed = (double)CAMERA_SPEED;
	game->player.dir.x = game->player.dir.x * cos(-speed) - game->player.dir.y
		* sin(-speed);
	game->player.dir.y = old_dir_x * sin(-speed) + game->player.dir.y * cos(-speed);
	game->player.plane.x = game->player.plane.x * cos(-speed)
		- game->player.plane.y * sin(-speed);
	game->player.plane.y = old_plane_x * sin(-speed) + game->player.plane.y
		* cos(-speed);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	speed = (double)CAMERA_SPEED;
	game->player.dir.x = game->player.dir.x * cos(speed) - game->player.dir.y
		* sin(speed);
	game->player.dir.y = old_dir_x * sin(speed) + game->player.dir.y * cos(speed);
	game->player.plane.x = game->player.plane.x * cos(speed)
		- game->player.plane.y * sin(speed);
	game->player.plane.y = old_plane_x * sin(speed) + game->player.plane.y
		* cos(speed);
}
