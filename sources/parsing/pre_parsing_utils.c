/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:23:48 by charline          #+#    #+#             */
/*   Updated: 2023/03/04 12:05:59 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_map_elems(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 'N' && line[i] != 'E' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != '0' && line[i] != '1'
			&& line[i] != ' ' && line[i] != '\n')
			return (error_msg("Wrong map elements\n"));
		i++;
	}
	return (0);
}

int	check_nb_coordinate(int *iter)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (iter[i] > 1)
			return (error_msg("Duplicate coordinate\n"));
		else if (iter[i] < 1)
			return (error_msg("Coordinate missing\n"));
		i++;
	}
	return (0);
}

int	mini_check_coordinate(int *iter)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (iter[i] < 1)
			return (-1);
		else if (iter[i] > 1)
			return (0);
		i++;
	}
	return (0);
}

int	find_coordinate(char *line, int *iter)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1] && line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		iter[0]++;
	else if (line[i] == 'E' && line[i + 1] == 'A')
		iter[1]++;
	else if (line[i] == 'S' && line[i + 1] == 'O')
		iter[2]++;
	else if (line[i] == 'W' && line[i + 1] == 'E')
		iter[3]++;
	else if (line[i] == 'F')
		iter[4]++;
	else if (line[i] == 'C')
		iter[5]++;
	else
		return (error_msg("Wrong coordinate\n"));
	return (0);
}
