/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:48:42 by samy              #+#    #+#             */
/*   Updated: 2023/06/28 11:13:46 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	main(int argc, char **argv)
{
	t_game	*game;

	game = parsing(argc, argv);
	print_game(game);
	game->window = mlx_new_window(game->mlx, 420, 420, "Cub3D");
	mlx_hook(game->window, DESTROYNOTIFY, 0, NULL, &game);
	mlx_loop(game->mlx);
	return (0);
}
