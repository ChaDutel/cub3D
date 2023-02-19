/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:39:55 by charline          #+#    #+#             */
/*   Updated: 2023/02/19 10:24:11 by maxperei         ###   ########lyon.fr   */
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
