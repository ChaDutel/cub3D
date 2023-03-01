/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:08:48 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/01 00:26:29 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	int	check_nb_player(t_config *config)
{
	int	i;
	int	j;
	int	nb_players;

	nb_players = 0;
	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
				nb_players++;
			j++;
		}
		i++;
	}
	if (nb_players != 1)
		return (-1);
	return (0);
}

static	int	is_wall(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

static	int	check_map_walls(t_config *config)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if ((i == 0 || i == config->y - 1 || j == 0 || j == config->x - 1)
				&& !is_wall(config->map[i][j]))
				return (-1);
			else if (!is_wall(config->map[i][j]) && (config->map[i - 1][j]
				== ' ' || config->map[i][j - 1] == ' ' || config->map[i + 1][j]
				== ' ' || config->map[i][j + 1] == ' '))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_map(t_config *config)
{
	if (check_nb_player(config))
		return (
			error_msg("There should be exactly 1 player on the map\n"));
	if (check_map_walls(config))
		return (error_msg("The map is not closed\n"));
	return (0);
}
