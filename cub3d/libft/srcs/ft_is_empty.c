/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:53:55 by sde-smed          #+#    #+#             */
/*   Updated: 2023/07/10 23:04:22 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_is_empty(char *str)
{
	while (str && *str)
	{
		if (!ft_is_space(*str))
			return (0);
		str++;
	}
	return (1);
}