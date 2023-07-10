/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:30:32 by samy              #+#    #+#             */
/*   Updated: 2023/07/10 11:39:18 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = -1;
	if (game->map)
	{
		while (game->map[++i] && i < game->map_height)
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
	if (message)
	{
		write(2, "Error\n", 6);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (game)
		free_game(game);
	exit(1);
}

void	error_parsing(char *message, t_game *game)
{
	if (game->fd)
		close(game->fd);
	if (game->map_list)
	{
		ft_lstclear(&game->map_list, free);
		game->map_list = NULL;
	}
	error(message, game);
}
