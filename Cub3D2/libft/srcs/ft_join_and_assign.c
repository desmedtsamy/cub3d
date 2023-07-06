/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_and_assign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:34:37 by sde-smed          #+#    #+#             */
/*   Updated: 2023/06/27 18:06:14 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_join_and_assign(char **result, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*result, str);
	if (!tmp)
		return (0);
	free(*result);
	*result = tmp;
	return (1);
}
