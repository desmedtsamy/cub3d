/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:08:31 by samy              #+#    #+#             */
/*   Updated: 2023/07/03 12:45:25 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game(t_game *game)
{
	int i;

	i = -1;
	if (game->map)
	{
		while (game->map[++i])
			free(game->map[i]);
		free(game->map);
	}
	if (game->mlx)
	{
		if (game->textures.no_texture)
			mlx_destroy_image(game->mlx, game->textures.no_texture);
		if (game->textures.so_texture)
			mlx_destroy_image(game->mlx, game->textures.so_texture);
		if (game->textures.we_texture)
			mlx_destroy_image(game->mlx, game->textures.we_texture);
		if (game->textures.ea_texture)
			mlx_destroy_image(game->mlx, game->textures.ea_texture);
		if (game->window)
			mlx_destroy_window(game->mlx, game->window);
	}
}

void	error(char *message, t_game *game)
{
	write(2, "Error\n", 6);
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (game)
		free_game(game);
	exit(1);
}

void	set_pos(int x, int y, t_pos *pos)
{
	pos->x = x;
	pos->y = y;
}

t_rect	*set_rect(t_pos *pos, t_pos *end_pos, t_rect *rect)
{
	rect->pos = pos;
	rect->end_pos = end_pos;
	return (rect);
}

void	draw_rect(t_rect *r, t_pos *max_p, int color, t_game *g)
{
	int		i;
	int		j;
	t_pos	max;
	t_pos	tmp;

	set_pos(MINI_SQUARE_SIZE, MINI_SQUARE_SIZE, &tmp);
	if (!r->end_pos)
		r->end_pos = &tmp;
	if (!max_p)
		set_pos(WIN_W, WIN_H, &max);
	else
		max = *max_p;
	i = 0;
	while (i < r->end_pos->y && r->pos->y + i < max.y)
	{
		j = 0;
		while (j < r->end_pos->x && r->pos->x + j < max.x)
		{
			mlx_pixel_put(g->mlx, g->window, r->pos->x + j, r->pos->y + i,
				color);
			j++;
		}
		i++;
	}
}
