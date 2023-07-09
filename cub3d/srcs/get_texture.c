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

static void	set_texture(t_game *game, char *path, void **texture,
		char *xpm_path)
{
	int	size;

	if (path)
	{
		write(2, xpm_path, ft_strlen(xpm_path));
		write(2, "\n", 1);
		error_parsing("Duplicate texture path", game);
	}
	path = ft_strdup(xpm_path);
	check_file(xpm_path, ".xpm", game);
	size = XPM_SIZE;
	*texture = mlx_xpm_file_to_image(game->mlx, xpm_path, &size, &size);
	if (!*texture)
	{
		write(2, xpm_path, ft_strlen(xpm_path));
		write(2, "\n", 1);
		error_parsing("Texture path is not valid", game);
	}
}

void	get_texture(char *pos, char *xpm_path, t_game *game)
{
	t_textures	*textures;

	textures = &game->textures;
	if (!xpm_path || ft_isempty(xpm_path))
		error_parsing("No texture path", game);
	if (xpm_path[ft_strlen(xpm_path) - 1] == '\n')
		xpm_path[ft_strlen(xpm_path) - 1] = '\0';
	if (ft_strcmp(pos, "NO") == 0)
		set_texture(game, textures->no_texture_path, &textures->no_texture,
			xpm_path);
	else if (ft_strcmp(pos, "SO") == 0)
		set_texture(game, textures->so_texture_path, &textures->so_texture,
			xpm_path);
	else if (ft_strcmp(pos, "WE") == 0)
		set_texture(game, textures->we_texture_path, &textures->we_texture,
			xpm_path);
	else if (ft_strcmp(pos, "EA") == 0)
		set_texture(game, textures->ea_texture_path, &textures->ea_texture,
			xpm_path);
	else
		error_parsing("Wrong texture path", game);
}
