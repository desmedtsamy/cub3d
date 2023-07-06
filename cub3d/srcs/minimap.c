/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:51:23 by samy              #+#    #+#             */
/*   Updated: 2023/07/06 15:50:52 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_cell(t_pos *pos, t_pos *test, char cell, t_game *game)
{
	t_rect		rect;
	t_minimap	*mini;
	t_pos		pos_max;

	set_pos((MINI_X + MINI_START), (MINI_Y + MINI_START), &pos_max);
	mini = &game->minimap;
	set_rect(pos, test, &rect);
	if (cell == '1')
		draw_rect(&rect, &pos_max, mini->wall_color, game);
	else if (is_accesible(cell))
		draw_rect(&rect, &pos_max, mini->floor_color, game);
}

void	print_map(float x, float y, t_pos *ofset, t_game *g)
{
	t_pos	pos;
	t_pos	size;
	int		i;
	int		j;

	pos.y = MINI_START;
	i = -1;
	while (++i + y < g->map_height && pos.y < (MINI_Y + MINI_START))
	{
		pos.x = MINI_START;
		j = -1;
		while (++j + x < g->map_width && pos.x < (MINI_X + MINI_START))
		{
			size.y = MINI_SQUARE_SIZE;
			size.x = MINI_SQUARE_SIZE;
			if (j == 0)
				size.x = MINI_SQUARE_SIZE - ofset->x;
			if (i == 0)
				size.y = MINI_SQUARE_SIZE - ofset->y;
			if (j + x >= 0 && i + y >= 0)
				print_cell(&pos, &size, g->map[(int)(i + y)][(int)(j + x)], g);
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
	draw_player(&pos, g->player.orientation, g);
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
}
