/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:33:04 by hgeissle          #+#    #+#             */
/*   Updated: 2023/07/10 13:50:52 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	get_pixel_color(t_game *game, int tex_x, int tex_y)
{
	unsigned int	color;

	game->line.pixel_tex = game->tex.addr + (tex_y * game->tex.sl + tex_x
			* (game->img.bpp / 8));
	color = *(unsigned int *)(game->line.pixel_tex);
	if (game->side == 1 && game->p.ray.y > 0)
		color = (color >> 1) & 8355711;
	return (color);
}

void	ft_mlx_pixel_put(t_game *game, int x, int y, unsigned int col)
{
	game->line.pixel_img = game->img.addr + (y * game->img.sl + x
			* (game->img.bpp / 8));
	*(unsigned int *)(game->line.pixel_img) = col;
}
