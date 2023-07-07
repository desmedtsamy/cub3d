/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:24:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/07/07 11:59:39 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	length_until_hit(double ray_dir_x, double ray_dir_y,
		t_game *game)
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	dist;

	map_x = (int)game->player.pos.x;
	map_y = (int)game->player.pos.y;
	game->player.delta.x = fabs(1 / ray_dir_x);
	if (ray_dir_x == 0)
		game->player.delta.x = 1e30;
	game->player.delta.y = fabs(1 / ray_dir_y);
	if (ray_dir_y == 0)
		game->player.delta.y = 1e30;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		game->player.side.x = (game->player.pos.x - map_x)
			* game->player.delta.x;
	}
	else
	{
		step_x = 1;
		game->player.side.x = (map_x + 1.0 - game->player.pos.x)
			* game->player.delta.x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		game->player.side.y = (game->player.pos.y - map_y)
			* game->player.delta.y;
	}
	else
	{
		step_y = 1;
		game->player.side.y = (map_y + 1.0 - game->player.pos.y)
			* game->player.delta.y;
	}
	while (1)
	{
		if (game->player.side.x < game->player.side.y)
		{
			game->player.side.x += game->player.delta.x;
			map_x += step_x;
			game->side = 0;
		}
		else
		{
			game->player.side.y += game->player.delta.y;
			map_y += step_y;
			game->side = 1;
		}
		if (game->map[map_y][map_x] == '1')
			break ;
	}
	if (game->side == 0)
		dist = (game->player.side.x - game->player.delta.x);
	else
		dist = (game->player.side.y - game->player.delta.y);
	return (dist);
}

int	get_texture_column(t_game *game, double dist, double ray_x, double ray_y)
{
	int		tex_x;
	double	wall_x;

	if (game->side == 0)
		wall_x = game->player.pos.y + dist * ray_y;
	else
		wall_x = game->player.pos.x + dist * ray_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)XPM_SIZE);
	if (game->side == 0 && ray_x > 0)
		tex_x = XPM_SIZE - tex_x - 1;
	if (game->side == 1 && ray_y < 0)
		tex_x = XPM_SIZE - tex_x - 1;
	return (tex_x);
}

void	floor_and_ceiling(t_game *game, int x)
{
	if (game->line.y < game->line.start)
	{
		game->line.pixel_img = game->img.addr + (game->line.y * game->img.sl + x
				* (game->img.bpp / 8));
		*(unsigned int *)(game->line.pixel_img) = game->ceiling_color;
	}
	else
	{
		game->line.pixel_img = game->img.addr + (game->line.y * game->img.sl + x
				* (game->img.bpp / 8));
		*(unsigned int *)(game->line.pixel_img) = game->floor_color;
	}
}

void	put_pixels_from_texture(t_game *game, double dist, int tex_x, int x)
{
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned int	color;

	game->line.height = (int)(WIN_H / dist);
	step = 1.0 * XPM_SIZE / game->line.height;
	game->line.y = 0;
	game->line.start = WIN_H / 2 - game->line.height / 2;
	if (game->line.start < 0)
		game->line.start = 0;
	tex_pos = (game->line.start - WIN_H / 2 + game->line.height / 2) * step;
	while (game->line.y < WIN_H)
	{
		if (game->line.y >= game->line.start && game->line.y < game->line.start
			+ game->line.height)
		{
			tex_y = (int)tex_pos & (XPM_SIZE - 1);
			tex_pos += step;
			game->line.pixel_tex = game->tex.addr + (tex_y * game->tex.sl
					+ tex_x * (game->img.bpp / 8));
			color = *(unsigned int *)(game->line.pixel_tex);
			if (game->side == 1)
				color = (color >> 1) & 8355711;
			game->line.pixel_img = game->img.addr + (game->line.y * game->img.sl
					+ x * (game->img.bpp / 8));
			*(unsigned int *)(game->line.pixel_img) = color;
		}
		else
			floor_and_ceiling(game, x);
		game->line.y++;
	}
}

void	*select_texture(t_game *game, double ray_dir_x, double ray_dir_y)
{
	void	*texture;

	if (game->side == 0 && ray_dir_x > 0)
		texture = game->textures.ea_texture;
	if (game->side == 0 && ray_dir_x < 0)
		texture = game->textures.we_texture;
	if (game->side == 1 && ray_dir_y > 0)
		texture = game->textures.so_texture;
	if (game->side == 1 && ray_dir_y < 0)
		texture = game->textures.no_texture;
	return (texture);
}

int	raycasting(t_game *game)
{
	double	screen_pos;
	double	ray_dir_x;
	double	ray_dir_y;
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
		screen_pos = 2 * (double)x / w - 1;
		ray_dir_x = game->player.dir.x + screen_pos * game->player.plane.x;
		ray_dir_y = game->player.dir.y + screen_pos * game->player.plane.y;
		dist = length_until_hit(ray_dir_x, ray_dir_y, game);
		tex_x = get_texture_column(game, dist, ray_dir_x, ray_dir_y);
		game->tex.ptr = select_texture(game, ray_dir_x, ray_dir_y);
		game->tex.addr = mlx_get_data_addr(game->tex.ptr, &game->tex.bpp,
				&game->tex.sl, &game->tex.endian);
		put_pixels_from_texture(game, dist, tex_x, x);
		x++;
	}
	return (0);
}
