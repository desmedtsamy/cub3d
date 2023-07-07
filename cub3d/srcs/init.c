/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:36:50 by samy              #+#    #+#             */
/*   Updated: 2023/07/07 11:06:39 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_minimap(t_game *game)
{
	t_minimap	*mini;

	mini = &game->minimap;
	mini->floor_color = game->floor_color;
	mini->bg_color = game->ceiling_color;
	mini->wall_color = WALL_COLOR;
	mini->player_color = PLAYER_COLOR;
}

t_data	*init_data(int fd, t_data *d)
{
	d->textures = 4;
	d->colors = 2;
	d->map = 0;
	d->line = get_next_line(fd);
	return (d);
}

t_game	*init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cub3D");
	game->textures.no_texture = NULL;
	game->textures.so_texture = NULL;
	game->textures.we_texture = NULL;
	game->textures.ea_texture = NULL;
	game->textures.no_texture_path = NULL;
	game->textures.so_texture_path = NULL;
	game->textures.we_texture_path = NULL;
	game->textures.ea_texture_path = NULL;
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
	return (game);
}

void	init_triangle(t_triangle *t, t_pos *p1, t_pos *p2, t_pos *p3)
{
	t->p1 = p1;
	t->p2 = p2;
	t->p3 = p3;
}
