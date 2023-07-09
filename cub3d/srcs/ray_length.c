/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:37:56 by hgeissle          #+#    #+#             */
/*   Updated: 2023/07/09 16:57:09 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_increment_values(t_game *game)
{
	game->p.map.x = (int)game->p.pos.x;
	game->p.map.y = (int)game->p.pos.y;
	game->p.delta.x = fabs(1 / game->p.ray.x);
	if (game->p.ray.x == 0)
		game->p.delta.x = 1e30;
	game->p.delta.y = fabs(1 / game->p.ray.y);
	if (game->p.ray.y == 0)
		game->p.delta.y = 1e30;
}

static void	get_ray_direction(t_game *game)
{
	get_increment_values(game);
	if (game->p.ray.x < 0)
	{
		game->p.step.x = -1;
		game->p.side.x = (game->p.pos.x - game->p.map.x) * game->p.delta.x;
	}
	else
	{
		game->p.step.x = 1;
		game->p.side.x = (game->p.map.x + 1.0 - game->p.pos.x)
			* game->p.delta.x;
	}
	if (game->p.ray.y < 0)
	{
		game->p.step.y = -1;
		game->p.side.y = (game->p.pos.y - game->p.map.y) * game->p.delta.y;
	}
	else
	{
		game->p.step.y = 1;
		game->p.side.y = (game->p.map.y + 1.0 - game->p.pos.y)
			* game->p.delta.y;
	}
}

double	length_until_hit(t_game *game)
{
	double	dist;

	get_ray_direction(game);
	while (1)
	{
		if (game->p.side.x < game->p.side.y)
		{
			game->p.side.x += game->p.delta.x;
			game->p.map.x += game->p.step.x;
			game->side = 0;
		}
		else
		{
			game->p.side.y += game->p.delta.y;
			game->p.map.y += game->p.step.y;
			game->side = 1;
		}
		if (game->map[game->p.map.y][game->p.map.x] == '1')
			break ;
	}
	if (game->side == 0)
		dist = (game->p.side.x - game->p.delta.x);
	else
		dist = (game->p.side.y - game->p.delta.y);
	return (dist);
}
