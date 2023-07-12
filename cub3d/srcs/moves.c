/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:16:51 by samy              #+#    #+#             */
/*   Updated: 2023/07/12 10:40:33 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	slide(t_game *game, int new_x, int new_y, int up_or_down)
{
	int		curr_x;
	int		curr_y;
	double	speed;

	curr_x = (int)game->p.pos.x;
	curr_y = (int)game->p.pos.y;
	speed = (double)SLIDE_SPEED;
	if (is_accesible(new_y, curr_x, game))
		game->p.pos.y -= (speed * up_or_down) * game->p.dir.y;
	else if (is_accesible(curr_y, new_x, game))
		game->p.pos.x -= (speed * up_or_down) * game->p.dir.x;
}

void	side_slide(t_game *game, int new_x, int new_y, int x)
{
	int		curr_x;
	int		curr_y;
	double	speed;

	curr_x = (int)game->p.pos.x;
	curr_y = (int)game->p.pos.y;
	speed = (double)SLIDE_SPEED;
	if (is_accesible(new_y, curr_x, game))
		game->p.pos.y += (speed * x) * game->p.dir.x;
	else if (is_accesible(curr_y, new_x, game))
		game->p.pos.x -= (speed * x) * game->p.dir.y;
}

void	move_forward(t_game *game, int x)
{
	double	speed;
	int		new_x;
	int		new_y;

	speed = (double)MOVE_SPEED;
	new_x = (int)(game->p.pos.x - (speed * x) * game->p.dir.x);
	new_y = (int)(game->p.pos.y - (speed * x) * game->p.dir.y);
	if (is_accesible(new_y, new_x, game))
	{
		game->p.pos.x -= (speed * x) * game->p.dir.x;
		game->p.pos.y -= (speed * x) * game->p.dir.y;
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
	new_x = (int)(game->p.pos.x - (speed * y) * game->p.dir.y);
	new_y = (int)(game->p.pos.y + (speed * y) * game->p.dir.x);
	if (is_accesible(new_y, new_x, game))
	{
		game->p.pos.x -= (speed * y) * game->p.dir.y;
		game->p.pos.y += (speed * y) * game->p.dir.x;
	}
	else
		side_slide(game, new_x, new_y, y);
}
