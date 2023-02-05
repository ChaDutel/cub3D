/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:44:33 by charline          #+#    #+#             */
/*   Updated: 2023/02/05 12:10:39 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	add_coordinate(char *line, int *elem_index, t_config *config)
{
	int	i;

	i = 0;
	if (line[0] != '\n')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
		{
			config->elems[*elem_index] = ft_strdup(&line[i]);
			if (!(config->elems[*elem_index]))
				return (-1);
			*elem_index += 1;
			config->elems[*elem_index] = NULL;
		}
	}
	return (0);
}

int	prepare_map(int fd, t_config *config)
{
	size_t	i;

	config->map = malloc(sizeof(char *) * (config->y + 1));
	if (!config->map)
	{
		close(fd);
		return (-1);
	}
	i = 0;
	while (i < config->y + 1)
	{
		config->map[i] = NULL;
		i++;
	}
	return (0);
}

void	trim_elems(t_config *config)
{
	int		i;

	i = 0;
	while (config->elems[i])
	{
		config->elems[i][ft_strlen(config->elems[i]) - 1] = '\0';
		i++;
	}
}

static	void	elem_swap(t_config *config, int a, int b)
{
	char	*tmp;

	tmp = config->elems[a];
	config->elems[a] = config->elems[b];
	config->elems[b] = tmp;
}

void	sort_elems(t_config *config)
{
	int	i;

	i = 1;
	while (config->elems[i] && config->elems[0][0] != 'N')
		elem_swap(config, 0, i++);
	i = 2;
	while (config->elems[i] && config->elems[1][0] != 'S')
		elem_swap(config, 1, i++);
	i = 3;
	while (config->elems[i] && config->elems[2][0] != 'E')
		elem_swap(config, 2, i++);
	i = 4;
	while (config->elems[i] && config->elems[3][0] != 'W')
		elem_swap(config, 3, i++);
	if (config->elems[4][0] != 'F')
		elem_swap(config, 4, 5);
}
