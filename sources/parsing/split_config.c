/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:32:54 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/01 20:51:30 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	int	add_coordinate(char *line, int *elem_index, t_config *config)
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
			config->elems[*elem_index + 1] = NULL;
		}
	}
	return (0);
}

static	int	fill_elems(int fd, t_config *config)
{
	int		elem_index;
	char	*line;

	config->elems = malloc(sizeof(char *) * 7);
	if (!config->elems)
		return (-1);
	config->elems[0] = NULL;
	elem_index = 0;
	while (elem_index != 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (-1);
		if (add_coordinate(line, &elem_index, config) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

static	int	fill_map(int fd, t_config *config)
{
	char	*line;

	line = get_next_line(fd);
	if (line ==)

	return (0);
}

int	split_config(char *config_file, t_config *config)
{
	int	fd;

	fd = open(config_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Error : cannot open the config file\n"));
	if (fill_elems(fd, config) == -1)
	{
		free_config(config);
		close(fd);
		return (error_msg("Error : malloc failed\n"));
	}
	if (fill_map(fd, config) == -1)
	{
		free_config(config);
		close(fd);
		return (error_msg("Error : malloc failed\n"));
	}
	// sort elems => NO SO EA WE F C
	close(fd);
	return (0);
}