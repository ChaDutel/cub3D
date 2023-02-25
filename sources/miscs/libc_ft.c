/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:39:55 by charline          #+#    #+#             */
/*   Updated: 2023/02/25 12:53:52 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float	roundint(int value)
{
	int	upper;
	int	lower;

	lower = value / TEXTURE_SIZE * TEXTURE_SIZE;
	upper = value + TEXTURE_SIZE;
	if (upper - value > value - lower)
		return ((float)lower);
	else
		return ((float)upper);
}

char	*char_join(char *str, char c)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!line)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			line[i] = str[i];
			i++;
		}
	}
	line[i++] = c;
	line[i] = '\0';
	return (line);
}
