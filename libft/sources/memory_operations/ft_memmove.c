/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:24:33 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 18:59:15 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (0);
	d = dst;
	s = (unsigned char *)src;
	if (s < d)
	{
		s += len;
		d += len;
		while (len --)
			*--d = *--s;
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
