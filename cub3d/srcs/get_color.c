/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:30:27 by samy              #+#    #+#             */
/*   Updated: 2023/07/11 21:37:46 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_color(char *str, t_game *game)
{
	char	*number;
	int		nb;

	number = ft_strtrim(str, " ");
	if (!number)
		error_parsing("Malloc error", game);
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

int	count_nb_chr(char c, char *str)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	while (str[++i])
		if (str[i] == c)
			nb++;
	return (nb);
}

void	get_color_value(int *color, char *str, t_game *game)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	if (ft_is_empty(str) || count_nb_chr(',', str) != 2)
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
