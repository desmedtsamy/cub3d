/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:08:31 by samy              #+#    #+#             */
/*   Updated: 2023/07/10 13:58:41 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_color_value(int *color, char *str, t_game *game)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	if (ft_isempty(str) || str[ft_strlen(str) - 1] == ',')
		error_parsing("bad elem in color", game);
	split = ft_split(str, ',');
	if (!split)
		error_parsing("Malloc error", game);
	if (ft_nb_split(split) != 3)
		error_parsing("bad elem in color", game);
	if (ft_strlen(split[0]) > 3 || ft_strlen(split[1]) > 3
		|| ft_strlen(split[2]) > 3)
		error_parsing("bad elem in color", game);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_parsing("bad elem in color", game);
	ft_free_split(split);
	*color = (r << 16 | g << 8 | b);
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
			ft_mlx_pixel_put(g, r->pos->x + j, r->pos->y + i, color);
			j++;
		}
		i++;
	}
}
