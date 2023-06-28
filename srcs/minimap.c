/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:51:23 by samy              #+#    #+#             */
/*   Updated: 2023/06/28 22:17:53 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_game *g, t_pos *pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(g->mlx, g->window, pos->x + j, pos->y + i, color);
			j++;
		}
		i++;
	}
}

void	init_minimap(t_game *game)
{
	t_minimap	*mini;

	mini = &game->minimap;
	mini->start_pos.x = MINIMAP_START_POS;
	mini->start_pos.y = MINIMAP_START_POS;
	mini->square_size = 10;
	mini->floor_color = 0x63656e;
	mini->bg_color = 0x1e202a;
	mini->wall_color = 0x2b2d3d;
	mini->player_color = 0xff0000;
}

void	draw_minimap(t_game *game)
{
	t_minimap	*mini;
	t_pos		pos;
	int			i;
	int			j;
	int			x;
	int			y;

	x = game->player.pos.x - ((MINIMAP_SIZE / 10) / 2);
	y = game->player.pos.y - ((MINIMAP_SIZE / 10) / 2);
	mini = &game->minimap;
	pos.x = mini->start_pos.x;
	pos.y = mini->start_pos.y;
	i = 0;
	draw_square(game, &mini->start_pos, MINIMAP_SIZE, mini->bg_color);
	while (i + y < game->map_height && i < (MINIMAP_SIZE / 10))
	{
		j = 0;
		while (j + x < game->map_width && j < (MINIMAP_SIZE / 10))
		{
			if (i + y < 0 || j + x < 0)
				draw_square(game, &pos, mini->square_size, mini->bg_color);
			else if (i + y == (int)game->player.pos.y && j
				+ x == (int)game->player.pos.x)
				draw_square(game, &pos, mini->square_size, mini->player_color);
			else if (game->map[i + y][j + x] == '1')
				draw_square(game, &pos, mini->square_size, mini->wall_color);
			else if (game->map[i + y][j + x] == '0')
				draw_square(game, &pos, mini->square_size, mini->floor_color);
			pos.x += mini->square_size;
			j++;
		}
		pos.x = mini->start_pos.x;
		pos.y += mini->square_size;
		i++;
	}
}

void	minimap(t_game *game)
{
	init_minimap(game);
	draw_minimap(game);
}
