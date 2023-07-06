/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:08:31 by samy              #+#    #+#             */
/*   Updated: 2023/07/06 22:53:24 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	img_pixel_put(int x, int y, int color, t_img img)
{
	char	*pixel_addr;

	pixel_addr = img.addr + (y * img.sl) + (x * (img.bpp / 8));
	if (img.endian == 0)
	{
		pixel_addr[0] = color & 0xFF;
		pixel_addr[1] = (color >> 8) & 0xFF;
		pixel_addr[2] = (color >> 16) & 0xFF;
	}
	else
	{
		pixel_addr[0] = (color >> 16) & 0xFF;
		pixel_addr[1] = (color >> 8) & 0xFF;
		pixel_addr[2] = color & 0xFF;
	}
}

void	draw_rect(t_rect *r, t_pos *max_p, int color, t_game *g)
{
	int		i;
	int		j;
	t_pos	max;
	t_pos	tmp;

	set_pos(MINI_SQUARE_SIZE, MINI_SQUARE_SIZE, &tmp);
	if (!r->end_pos)
		r->end_pos = &tmp;
	if (!max_p)
		set_pos(WIN_W, WIN_H, &max);
	else
		max = *max_p;
	i = 0;
	while (i < r->end_pos->y && r->pos->y + i < max.y)
	{
		j = 0;
		while (j < r->end_pos->x && r->pos->x + j < max.x)
		{
			img_pixel_put (r->pos->x + j, r->pos->y + i, color, g->img);
			j++;
		}
		i++;
	}
}
