/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:55:00 by samy              #+#    #+#             */
/*   Updated: 2023/06/27 17:39:52 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_start_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_accesible(char c)
{
	if (c == '0' || is_start_pos(c))
		return (1);
	return (0);
}

int	is_valid_elem(char c)
{
	if (c == '1' || c == ' ' || is_accesible(c))
		return (1);
	return (0);
}
