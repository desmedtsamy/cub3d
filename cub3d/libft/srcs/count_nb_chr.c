/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nb_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:27:23 by sde-smed          #+#    #+#             */
/*   Updated: 2023/07/12 10:27:45 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
