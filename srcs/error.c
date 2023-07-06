/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:30:32 by samy              #+#    #+#             */
/*   Updated: 2023/07/05 20:36:22 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game(t_game *game)
{
	int	i;

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
		else if (game->textures.so_texture)
			mlx_destroy_image(game->mlx, game->textures.so_texture);
		else if (game->textures.we_texture)
			mlx_destroy_image(game->mlx, game->textures.we_texture);
		else if (game->textures.ea_texture)
			mlx_destroy_image(game->mlx, game->textures.ea_texture);
		else if (game->window)
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

void	error_parsing(int fd, t_game *game)
{
	if (fd)
		close(fd);
	error("invalid data in cub file", game);
}
