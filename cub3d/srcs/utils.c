/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:08:31 by samy              #+#    #+#             */
/*   Updated: 2023/07/11 21:30:43 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			ft_mlx_pixel_put(g, r->pos->x + j, r->pos->y + i, color);
			j++;
		}
		i++;
	}
}
