/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:36:50 by samy              #+#    #+#             */
/*   Updated: 2023/07/02 00:39:16 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_minimap(t_game *game)
{
	t_minimap	*mini;

	mini = &game->minimap;
	mini->floor_color = 0x63656e;
	mini->bg_color = 0x1e202a;
	mini->wall_color = 0x2b2d3d;
	mini->player_color = 0xff0000;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error("Malloc error", NULL);
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
	return (game);
}
