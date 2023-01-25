/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:58:10 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 19:00:23 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	i = ft_strlen(dst);
	dstlen = i;
	srclen = ft_strlen(src);
	if (dstsize <= i)
		return (srclen + dstsize);
	j = 0;
	while (j < dstsize - dstlen - 1 && src[j] && (i + 1) < dstsize)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (srclen + dstlen);
}
