/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:40:55 by samy              #+#    #+#             */
/*   Updated: 2023/06/27 17:41:23 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_texture(t_game *game, void **texture, char *xpm_path)
{
	int	size;

	if (*texture)
		error_parsing("Duplicate texture path", game);
	check_file(xpm_path, ".xpm", game);
	size = XPM_SIZE;
	*texture = mlx_xpm_file_to_image(game->mlx, xpm_path, &size, &size);
	if (!*texture)
		error_parsing("Texture path is not valid", game);
}

void	get_texture(char *pos, char *xpm_path, t_game *game)
{
	t_textures	*textures;

	textures = &game->textures;
	if (!xpm_path || ft_is_empty(xpm_path))
		error_parsing("No texture path", game);
	if (ft_strcmp(pos, "NO") == 0)
		set_texture(game, &textures->no_texture, xpm_path);
	else if (ft_strcmp(pos, "SO") == 0)
		set_texture(game, &textures->so_texture, xpm_path);
	else if (ft_strcmp(pos, "WE") == 0)
		set_texture(game, &textures->we_texture, xpm_path);
	else if (ft_strcmp(pos, "EA") == 0)
		set_texture(game, &textures->ea_texture, xpm_path);
	else
		error_parsing("Wrong texture path", game);
}
