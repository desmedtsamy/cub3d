/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:48:42 by samy              #+#    #+#             */
/*   Updated: 2023/07/03 13:19:16 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	quit(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
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
	t_pos	*player_pos;

	game = (t_game *)param;
	player_pos = &game->player.pos;
	if (game->move.forward)
		move((player_pos->x), (player_pos->y - SPEED), game);
	if (game->move.backward)
		move((player_pos->x), (player_pos->y + SPEED), game);
	if (game->move.left)
		move((player_pos->x - SPEED), (player_pos->y), game);
	if (game->move.right)
		move((player_pos->x + SPEED), (player_pos->y), game);
	//if (game->move.forward || game->move.backward || game->move.left
	//	|| game->move.right)
		minimap(game);
	return (0);
}

static int	deal_keys(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == ESC_KEY)
		quit(param);
	else if (key == UP)
		game->move.forward = 1;
	else if (key == DOWN)
		game->move.backward = 1;
	else if (key == LEFT)
		game->move.left = 1;
	else if (key == RIGHT)
		game->move.right = 1;
	else if (key == LEFT_ARROW)
		game->player.orientation -= 15;
	else if (key == RIGHT_ARROW)
		game->player.orientation += 15;
	return (0);
}

static int	deal_keys_release(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == UP)
		game->move.forward = 0;
	else if (key == DOWN)
		game->move.backward = 0;
	else if (key == LEFT)
		game->move.left = 0;
	else if (key == RIGHT)
		game->move.right = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	parsing(argc, argv, &game);
	print_game(&game);
	init_minimap(&game);
	minimap(&game);
	mlx_hook(game.window, KEYPRESS, (1L << 0), deal_keys, &game);
	mlx_hook(game.window, KEYRELEASE, (1L << 1), deal_keys_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_hook(game.window, DESTROYNOTIFY, 0, quit, &game);
	mlx_loop(game.mlx);
	return (0);
}
