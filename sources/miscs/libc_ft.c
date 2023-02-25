/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:39:55 by charline          #+#    #+#             */
/*   Updated: 2023/02/25 13:33:22 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

float	fix_ang(float a)
{
	if (a > 359.0)
		a -= 360.0;
	if (a < 0.0)
		a += 360.0;
	return (a);
}

float	deg_to_rad(float a)
{
	return (a * PI / 180.0);
}
