/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:48:42 by samy              #+#    #+#             */
/*   Updated: 2023/06/28 22:18:40 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	quit(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_destroy_image(game->mlx, game->textures.no_texture);
	mlx_destroy_image(game->mlx, game->textures.so_texture);
	mlx_destroy_image(game->mlx, game->textures.we_texture);
	mlx_destroy_image(game->mlx, game->textures.ea_texture);
	mlx_destroy_window(game->mlx, game->window);
	exit(0);
	return (0);
}

void	print_binary_rgb(int rgb)
{
	int	i;

	i = 0;
	while (i < 24)
	{
		printf("%d", (rgb >> i) & 1);
		i++;
	}
	printf("\n");
}

void	print_game(t_game *game)
{
	int	i;

	i = 0;
	printf("NO: %s\n", game->textures.no_texture_path);
	printf("SO: %s\n", game->textures.so_texture_path);
	printf("WE: %s\n", game->textures.we_texture_path);
	printf("EA: %s\n", game->textures.ea_texture_path);
	print_binary_rgb(game->ceiling_color);
	print_binary_rgb(game->floor_color);
	printf("Map width: %d\n", game->map_width);
	printf("Map height: %d\n", game->map_height);
	while (i < game->map_height)
		printf("%s\n", game->map[i++]);
}

static int	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->move.forward)
		game->player.pos.y -= 1;
	if (game->move.backward)
		game->player.pos.y += 1;
	if (game->move.left)
		game->player.pos.x -= 1;
	if (game->move.right)
		game->player.pos.x += 1;
	draw_minimap(game);
	return (0);
}

static int	deal_keys(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == 53)
		quit(param);
	else if (key == 13)
		game->move.forward = 1;
	else if (key == 1)
		game->move.backward = 1;
	else if (key == 0)
		game->move.left = 1;
	else if (key == 2)
		game->move.right = 1;
	return (0);
}

static int	deal_keys_release(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == 13)
		game->move.forward = 0;
	else if (key == 1)
		game->move.backward = 0;
	else if (key == 0)
		game->move.left = 0;
	else if (key == 2)
		game->move.right = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = parsing(argc, argv);
	print_game(game);
	minimap(game);
	mlx_hook(game->window, KEYPRESS, (1L << 0), deal_keys, game);
	mlx_hook(game->window, KEYRELEASE, (1L << 1), deal_keys_release, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_hook(game->window, DESTROYNOTIFY, 0, quit, game);
	mlx_loop(game->mlx);
	return (0);
}
