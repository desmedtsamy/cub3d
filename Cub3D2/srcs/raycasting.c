/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:24:55 by hgeissle          #+#    #+#             */
/*   Updated: 2023/07/06 14:16:28 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	length_until_hit(double ray_dir_x, double ray_dir_y, t_game *game)
{
	int	map_x;
	int	map_y;
	int	step_x;
	int	step_y;
	double	dist;

	map_x = (int)game->player.pos.x;
	map_y = (int)game->player.pos.y;
	// game->player.delta.x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
	// game->player.delta.y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
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
		// printf("side x %f delta x %f side y %f delta y %f\n", game->player.side.x, game->player.delta.x, game->player.side.y, game->player.delta.y);
		if (game->map[map_y][map_x] == '1')
			break ;
	}
	// printf("%d %d\n", map_x, map_y);
	if (game->side == 0)
		dist = (game->player.side.x - game->player.delta.x);
	else
		dist = (game->player.side.y - game->player.delta.y);
	return (dist);
}

int	get_texture_column(t_game *game, double dist)
{
	int			tex_x;
	double		wall_x;

	if (game->side == 0)
		wall_x = game->player.pos.y + dist * game->player.dir.y;
	else
		wall_x = game->player.pos.x + dist * game->player.dir.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)XPM_SIZE);
	if (game->side == 0 && game->player.dir.x > 0)
		tex_x = XPM_SIZE - tex_x - 1;
	if (game->side == 1 && game->player.dir.y < 0)
		tex_x = XPM_SIZE - tex_x - 1;
	return (tex_x);
}

void	put_pixels_from_texture(t_game *game, t_img *img, t_img *tex, double dist, int tex_x, int x)
{
	double			step;
	double			tex_pos;
	int				tex_y;
	int				line_height;
	int				y;
	unsigned int	color;
	char			*pixel_tex;
	char			*pixel_img;

	line_height = (int)(WIN_H / dist);
	step = 1.0 * XPM_SIZE / line_height;
	// printf("pkkkkk\n");
	y = WIN_H / 2 - line_height / 2;
	if (y < 0)
		y = 0;
	tex_pos = (y - WIN_H / 2 + line_height / 2) * step;
	while (y < WIN_H / 2 + line_height / 2 && y < WIN_H)
	{
		// printf("x %d y %d\n", x, y);
		tex_y = (int)tex_pos & (XPM_SIZE - 1);
		tex_pos += step;
		pixel_tex = tex->addr + (tex_y * tex->sl + tex_x * (img->bpp / 8));
		color = *(unsigned int *)(pixel_tex);
	    if (game->side == 1)
			color = (color >> 1) & 8355711;
		pixel_img = img->addr + (y * img->sl + x * (img->bpp / 8));
		*(unsigned int *)(pixel_img) = color;
		y++;
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
	int			tex_x;
	t_img	*img;
	t_img	*tex;

	x = 0;
	w = (double)WIN_W;
	img = malloc(sizeof(t_img));
	tex = malloc(sizeof(t_img));
	// printf("Value of img: %p\n", img);
	// printf("Value of tex: %p\n", tex);
	// printf("Values of WIN_W and WIN_H: %d, %d\n", WIN_W, WIN_H);
	img->ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->sl, &img->endian);
	while (x < WIN_W - 1)
	{
		screen_pos = 2 * (double)x / w - 1;
		ray_dir_x = game->player.dir.x + screen_pos * game->player.plane.x;
		ray_dir_y = game->player.dir.y + screen_pos * game->player.plane.y;
		dist = length_until_hit(ray_dir_x, ray_dir_y, game);
		tex_x = get_texture_column(game, dist);
		tex->ptr = select_texture(game, ray_dir_x, ray_dir_y);
		tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->sl, &tex->endian);
		// printf("Value of img: %p\n", img);
		// printf("Value of tex: %p\n", tex);
		// printf("Value of game: %p\n", game);
		// printf("Value of tex_x: %d\n", tex_x);
		// printf("Value of x: %d\n", x);
		// printf("Value of dist: %f\n", dist);
		// printf("Value of fct: %p\n", &put_pixels_from_texture);
		put_pixels_from_texture(game, img, tex, dist, tex_x, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->window, img->ptr, 0, 0);
	mlx_destroy_image(game->mlx, img->ptr);
	return (0);
}
