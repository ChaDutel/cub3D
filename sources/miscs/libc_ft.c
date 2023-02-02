/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:39:55 by charline          #+#    #+#             */
/*   Updated: 2023/02/02 22:48:51 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char    *char_join(char *str, char c)
{
    int     i;
    char    *line;

    i = 0;
    line = malloc(sizeof(char) * (ft_strlen(str) + 2));
    if (!line)
        return (NULL);
    while (str[i])
    {
        line[i] = str[i];
        i++;
    }
    line[i++] = c;
    line[i] = '\0';
    return (line);
}