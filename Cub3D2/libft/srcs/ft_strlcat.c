/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:38 by samy              #+#    #+#             */
/*   Updated: 2023/06/27 18:06:14 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_start_size;
	size_t	src_size;

	if (!dstsize && !dst)
		return (0);
	i = 0;
	dst_start_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	dst += dst_start_size;
	if (dstsize < dst_start_size + 1)
		return (src_size + dstsize);
	while (src[i] && (dst_start_size + i + 1) < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst_start_size + src_size);
}
