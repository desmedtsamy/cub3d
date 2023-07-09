/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:24:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/07/09 17:40:52 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	floor_and_ceiling(t_game *game, int x)
{
	if (game->line.y < game->line.start)
		ft_mlx_pixel_put(game, x, game->line.y, game->ceiling_color);
	else
		ft_mlx_pixel_put(game, x, game->line.y, game->floor_color);
}

static void	init_vertical_line(t_game *game, double dist)
{
	game->line.height = (int)((double)WIN_H / dist);
	game->line.y = 0;
	game->line.start = WIN_H / 2 - game->line.height / 2;
	if (game->line.start < 0)
		game->line.start = 0;
}

static void	put_pixels_from_texture(t_game *game, double dist, int tex_x, int x)
{
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned int	color;

	init_vertical_line(game, dist);
	step = 1.0 * XPM_SIZE / game->line.height;
	tex_pos = (game->line.start - WIN_H / 2 + game->line.height / 2) * step;
	while (game->line.y < WIN_H)
	{
		if (game->line.y >= game->line.start && game->line.y < game->line.start
			+ game->line.height)
		{
			tex_y = (int)tex_pos & (XPM_SIZE - 1);
			tex_pos += step;
			color = get_pixel_color(game, tex_x, tex_y);
			ft_mlx_pixel_put(game, x, game->line.y, color);
		}
		else
			floor_and_ceiling(game, x);
		game->line.y++;
	}
}

int	raycasting(t_game *game)
{
	double	win_x;
	int		x;
	double	dist;
	double	w;
	int		tex_x;

	x = 0;
	w = (double)WIN_W;
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.sl, &game->img.endian);
	while (x < WIN_W - 1)
	{
		win_x = 2 * (double)x / w - 1;
		game->p.ray.x = game->p.dir.x + win_x * game->p.plane.x;
		game->p.ray.y = game->p.dir.y + win_x * game->p.plane.y;
		dist = length_until_hit(game);
		tex_x = get_texture_column(game, dist);
		game->tex.ptr = select_texture(game);
		game->tex.addr = mlx_get_data_addr(game->tex.ptr, &game->tex.bpp,
				&game->tex.sl, &game->tex.endian);
		put_pixels_from_texture(game, dist, tex_x, x);
		x++;
	}
	return (0);
}
