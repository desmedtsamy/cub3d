/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:36:50 by samy              #+#    #+#             */
/*   Updated: 2023/07/10 22:00:22 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_minimap(t_game *game)
{
	game->minimap.floor_color = game->floor_color;
	game->minimap.bg_color = game->ceiling_color;
	game->minimap.wall_color = WALL_COLOR;
	game->minimap.player_color = PLAYER_COLOR;
}

t_data	*init_data(t_data *d)
{
	d->textures = 4;
	d->colors = 2;
	d->map = 0;
	d->line = NULL;
	d->name = NULL;
	d->value = NULL;
	return (d);
}

static void	init_textures(t_textures *textures)
{
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
}

t_game	*init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cub3D");
	game->map_width = 0;
	game->map_height = 0;
	game->map = NULL;
	game->map_list = NULL;
	game->move.forward = 0;
	game->move.backward = 0;
	game->move.left = 0;
	game->move.right = 0;
	game->move.turn_left = 0;
	game->move.turn_right = 0;
	game->fd = 0;
	init_textures(&game->textures);
	return (game);
}

void	init_triangle(t_triangle *t, t_pos *p1, t_pos *p2, t_pos *p3)
{
	t->p1 = p1;
	t->p2 = p2;
	t->p3 = p3;
}
