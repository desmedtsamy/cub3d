/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:08:31 by samy              #+#    #+#             */
/*   Updated: 2023/07/10 23:00:24 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_color(char *str, t_game *game)
{
	char	*number;
	int		nb;

	number = ft_strtrim(str, " ");
	nb = -1;
	while (number[++nb])
		if (!ft_isdigit(number[nb]))
			error_parsing("bad elem in color", game);
	if (ft_strlen(number) > 3)
		error_parsing("bad elem in color", game);
	nb = ft_atoi(number);
	if (nb < 0 || nb > 255)
		error_parsing("bad elem in color", game);
	return (nb);
}

void	get_color_value(int *color, char *str, t_game *game)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	if (ft_is_empty(str) || str[ft_strlen(str) - 1] == ',')
		error_parsing("bad elem in color", game);
	split = ft_split(str, ',');
	if (!split)
		error_parsing("Malloc error", game);
	if (ft_nb_split(split) != 3)
		error_parsing("bad elem in color", game);
	r = get_color(split[0], game);
	g = get_color(split[1], game);
	b = get_color(split[2], game);
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
