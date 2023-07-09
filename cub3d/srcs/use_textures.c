/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:52:32 by hgeissle          #+#    #+#             */
/*   Updated: 2023/07/09 16:56:24 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_column(t_game *game, double dist)
{
	int		tex_x;
	double	wall_x;

	if (game->side == 0)
		wall_x = game->p.pos.y + dist * game->p.ray.y;
	else
		wall_x = game->p.pos.x + dist * game->p.ray.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)XPM_SIZE);
	if (game->side == 0 && game->p.ray.x < 0)
		tex_x = XPM_SIZE - tex_x - 1;
	if (game->side == 1 && game->p.ray.y > 0)
		tex_x = XPM_SIZE - tex_x - 1;
	return (tex_x);
}

void	*select_texture(t_game *game)
{
	void	*texture;

	if (game->side == 0 && game->p.ray.x > 0)
		texture = game->textures.ea_texture;
	if (game->side == 0 && game->p.ray.x < 0)
		texture = game->textures.we_texture;
	if (game->side == 1 && game->p.ray.y > 0)
		texture = game->textures.so_texture;
	if (game->side == 1 && game->p.ray.y < 0)
		texture = game->textures.no_texture;
	return (texture);
}
