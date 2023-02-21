/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:39:55 by charline          #+#    #+#             */
/*   Updated: 2023/02/21 00:47:14 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int roundint(int value)
{
	int	upper;
	int	lower;

	lower = value / TEXTURE_SIZE * TEXTURE_SIZE;
	upper = value + TEXTURE_SIZE;
	if (upper - value > value - lower)
		return (lower);
	else
		return (upper);
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
