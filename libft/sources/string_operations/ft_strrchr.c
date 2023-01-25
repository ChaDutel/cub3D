/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:09:22 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 19:00:47 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*p;

	i = 0;
	len = ft_strlen(s);
	p = 0;
	while (i < len + 1)
	{
		if (s[i] == (char) c)
			p = (char *)&s[i];
		i++;
	}
	return (p);
}
