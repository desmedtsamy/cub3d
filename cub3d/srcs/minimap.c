/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:51:23 by samy              #+#    #+#             */
/*   Updated: 2023/07/06 22:50:05 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_cell(t_pos *pos, t_pos *test, t_pos *elem, t_game *game)
{
	t_rect		rect;
	t_minimap	*mini;
	t_pos		pos_max;

	set_pos((MINI_X + MINI_START), (MINI_Y + MINI_START), &pos_max);
	mini = &game->minimap;
	set_rect(pos, test, &rect);
	if (game->map[(int)elem->y][(int)elem->x] == '1')
		draw_rect(&rect, &pos_max, mini->wall_color, game);
	else if (is_accesible(elem->y, elem->x, game))
		draw_rect(&rect, &pos_max, mini->floor_color, game);
}

void	print_map(float x, float y, t_pos *ofset, t_game *g)
{
	t_pos	pos;
	t_pos	size;
	t_pos	elem;
	t_pos	mini;

	pos.y = MINI_START;
	mini.y = -1;
	while (++mini.y + y < g->map_height && pos.y < (MINI_Y + MINI_START))
	{
		pos.x = MINI_START;
		mini.x = -1;
		while (++mini.x + x < g->map_width && pos.x < (MINI_X + MINI_START))
		{
			set_pos(MINI_SQUARE_SIZE, MINI_SQUARE_SIZE, &size);
			if (mini.x == 0)
				size.x = MINI_SQUARE_SIZE - ofset->x;
			if (mini.y == 0)
				size.y = MINI_SQUARE_SIZE - ofset->y;
			set_pos((mini.x + x), (mini.y + y), &elem);
			if (mini.x + x >= 0 && mini.y + y >= 0)
				print_cell(&pos, &size, &elem, g);
			pos.x += size.x;
		}
		pos.y += size.y;
	}
}

void	draw_minimap(t_pos *start, t_pos *size, t_pos *pos_max, t_game *g)
{
	t_pos	pos;
	t_pos	ofset;
	t_rect	rect;
	float	x;
	float	y;

	x = g->player.pos.x - ((MINI_X / MINI_SQUARE_SIZE) / 2);
	y = g->player.pos.y - ((MINI_Y / MINI_SQUARE_SIZE) / 2);
	set_pos((g->player.pos.x - (int)g->player.pos.x) * MINI_SQUARE_SIZE,
		(g->player.pos.y - (int)g->player.pos.y) * MINI_SQUARE_SIZE,
		&ofset);
	draw_rect(set_rect(start, size, &rect), pos_max, g->minimap.bg_color, g);
	print_map(x, y, &ofset, g);
	set_pos((MINI_X / 2) + MINI_START - MINI_SQUARE_SIZE / 2, (MINI_Y / 2)
		+ MINI_START - MINI_SQUARE_SIZE / 2, &pos);
	draw_rect(set_rect(&pos, NULL, &rect), pos_max, g->minimap.player_color, g);
}

void	minimap(t_game *game)
{
	t_pos	size;
	t_pos	start;
	t_pos	pos_max;

	set_pos(MINI_START, MINI_START, &start);
	set_pos(MINI_X, MINI_Y, &size);
	set_pos((MINI_X + MINI_START), (MINI_Y + MINI_START), &pos_max);
	draw_minimap(&start, &size, &pos_max, game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.ptr, 0, 0);
	mlx_destroy_image(game->mlx, game->img.ptr);
}
