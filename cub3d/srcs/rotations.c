/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:05:01 by hgeissle          #+#    #+#             */
/*   Updated: 2023/07/09 17:05:55 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = game->p.dir.x;
	old_plane_x = game->p.plane.x;
	speed = (double)CAMERA_SPEED;
	game->p.dir.x = game->p.dir.x * cos(-speed) - game->p.dir.y
		* sin(-speed);
	game->p.dir.y = old_dir_x * sin(-speed) + game->p.dir.y * cos(-speed);
	game->p.plane.x = game->p.plane.x * cos(-speed)
		- game->p.plane.y * sin(-speed);
	game->p.plane.y = old_plane_x * sin(-speed) + game->p.plane.y
		* cos(-speed);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = game->p.dir.x;
	old_plane_x = game->p.plane.x;
	speed = (double)CAMERA_SPEED;
	game->p.dir.x = game->p.dir.x * cos(speed) - game->p.dir.y
		* sin(speed);
	game->p.dir.y = old_dir_x * sin(speed) + game->p.dir.y * cos(speed);
	game->p.plane.x = game->p.plane.x * cos(speed)
		- game->p.plane.y * sin(speed);
	game->p.plane.y = old_plane_x * sin(speed) + game->p.plane.y
		* cos(speed);
}
