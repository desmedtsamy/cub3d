/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:48:42 by samy              #+#    #+#             */
/*   Updated: 2023/07/11 12:04:17 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	quit(void *param)
{
	free_game((t_game *)param);
	exit(0);
}

static int	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->move.forward)
		move_forward(game, -1);
	if (game->move.backward)
		move_forward(game, 1);
	if (game->move.left)
		move_sideways(game, -1);
	if (game->move.right)
		move_sideways(game, 1);
	if (game->move.turn_left)
		rotate_left(game);
	if (game->move.turn_right)
		rotate_right(game);
	if (game->move.forward || game->move.backward || game->move.left
		|| game->move.right || game->move.turn_right || game->move.turn_left)
	{
		mlx_clear_window(game->mlx, game->window);
		raycasting(game);
		minimap(game);
		mlx_put_image_to_window(game->mlx, game->window, game->img.ptr, 0, 0);
		mlx_destroy_image(game->mlx, game->img.ptr);
	}
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
		game->move.turn_left = 1;
	else if (key == RIGHT_ARROW)
		game->move.turn_right = 1;
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
	else if (key == LEFT_ARROW)
		game->move.turn_left = 0;
	else if (key == RIGHT_ARROW)
		game->move.turn_right = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (WIN_H < 10 || WIN_W < 10)
		ft_putstr_fd("Window size is too small\n", 2);
	parsing(argc, argv, &game);
	raycasting(&game);
	init_minimap(&game);
	if (MINI_X + MINI_START > WIN_W || MINI_Y + MINI_START > WIN_H)
		ft_putstr_fd("can't print minimap, size is too big\n", 2);
	else
		minimap(&game);
	mlx_put_image_to_window(game.mlx, game.window, game.img.ptr, 0, 0);
	mlx_destroy_image(game.mlx, game.img.ptr);
	mlx_hook(game.window, KEYPRESS, (1L << 0), deal_keys, &game);
	mlx_hook(game.window, KEYRELEASE, (1L << 1), deal_keys_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_hook(game.window, DESTROYNOTIFY, 0, quit, &game);
	mlx_loop(game.mlx);
	return (0);
}
