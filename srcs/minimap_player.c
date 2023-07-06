/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:37:53 by samy              #+#    #+#             */
/*   Updated: 2023/07/05 20:34:40 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	point_in_triangle(const t_pos *point, t_triangle *t)
{
	float	gamma;
	float	alpha;
	float	beta;

	alpha = ((t->p2->y - t->p3->y) * (point->x - t->p3->x) + (t->p3->x
				- t->p2->x) * (point->y - t->p3->y)) / ((t->p2->y - t->p3->y)
			* (t->p1->x - t->p3->x) + (t->p3->x - t->p2->x) * (t->p1->y
				- t->p3->y));
	beta = ((t->p3->y - t->p1->y) * (point->x - t->p3->x) + (t->p1->x
				- t->p3->x) * (point->y - t->p3->y)) / ((t->p2->y - t->p3->y)
			* (t->p1->x - t->p3->x) + (t->p3->x - t->p2->x) * (t->p1->y
				- t->p3->y));
	gamma = 1.0f - alpha - beta;
	return (alpha >= 0 && beta >= 0 && gamma >= 0);
}

static void	rotate_point(t_pos *point, const t_pos *center, float angle)
{
	float	s;
	float	c;
	float	new_x;
	float	new_y;

	s = sin(angle);
	c = cos(angle);
	new_x = (point->x - center->x) * c - (point->y - center->y) * s + center->x;
	new_y = (point->x - center->x) * s + (point->y - center->y) * c + center->y;
	point->x = new_x;
	point->y = new_y;
}

static void	fill_triangle(t_triangle *t, int color,
		t_game *game)
{
	t_pos	min_pos;
	t_pos	max_pos;
	t_pos	current_pos;

	min_pos.x = fmin(t->p1->x, fmin(t->p2->x, t->p3->x));
	min_pos.y = fmin(t->p1->y, fmin(t->p2->y, t->p3->y));
	max_pos.x = fmax(t->p1->x, fmax(t->p2->x, t->p3->x));
	max_pos.y = fmax(t->p1->y, fmax(t->p2->y, t->p3->y));
	current_pos.y = min_pos.y;
	while (current_pos.y <= max_pos.y)
	{
		current_pos.x = min_pos.x;
		while (current_pos.x <= max_pos.x)
		{
			if (point_in_triangle(&current_pos, t))
				mlx_pixel_put(game->mlx, game->window, current_pos.x,
					current_pos.y, color);
			current_pos.x++;
		}
		current_pos.y++;
	}
}

void	draw_player(t_pos *pos, float angle, t_game *game)
{
	float		height;
	t_pos		p1;
	t_pos		p2;
	t_pos		p3;
	t_triangle	t;

	height = PLAYER_SIZE * sin(M_PI / 3);
	set_pos(pos->x, pos->y - height, &p1);
	set_pos(pos->x - PLAYER_SIZE / 2, pos->y + height / 2, &p2);
	set_pos(pos->x + PLAYER_SIZE / 2, pos->y + height / 2, &p3);
	init_triangle(&t, &p1, &p2, &p3);
	rotate_point(t.p1, pos, angle);
	rotate_point(t.p2, pos, angle);
	rotate_point(t.p3, pos, angle);
	fill_triangle(&t, game->minimap.player_color, game);
}
