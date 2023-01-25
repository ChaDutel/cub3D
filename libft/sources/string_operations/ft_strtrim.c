/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:03:33 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 19:00:51 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	if (size == 0)
		return (ft_substr(s1, 0, size));
	size--;
	while (&*s1 != &s1[size] && ft_strchr(set, s1[size]))
		size--;
	return (ft_substr(s1, 0, size + 1));
}
