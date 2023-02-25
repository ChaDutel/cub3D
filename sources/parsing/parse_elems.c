/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:45:04 by charline          #+#    #+#             */
/*   Updated: 2023/02/05 12:11:03 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	check_colors(t_config *config)
{
	int	i;
	int	j;

	i = 4;
	while (config->elems[i])
	{
		j = 1;
		if (check_colors_values(config, i, j) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	parse_elems(t_config *config)
{
	int	fd;
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 2;
		while (config->elems[i][j] && config->elems[i][j] == ' ')
			j++;
		fd = open(&config->elems[i][j], O_RDONLY);
		if (fd == -1)
			return (error_msg("Error : Wrong texture path\n"));
		close(fd);
		fd = open(&config->elems[i][j], __O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			return (error_msg("Error : Texture path is a directory\n"));
		}
		i++;
	}
	if (check_colors(config) == -1)
		return (-1);
	return (0);
}
