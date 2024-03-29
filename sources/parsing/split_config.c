/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:32:54 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/02 15:17:20 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

static	int	map_mesurer(int fd, t_config *config)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	config->y = 0;
	config->x = 0;
	while (line)
	{
		config->y++;
		if (ft_strlen(line) - 1 > config->x)
			config->x = ft_strlen(line) - 1;
		if (config->x * config->y > MAX_AREA)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

static	void	line_copy(char *line, t_config *config, int *i)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		config->map[*i][j] = line[j];
		j++;
	}
	while (j < (int)config->x)
	{
		config->map[*i][j] = ' ';
		j++;
	}
	config->map[*i][j] = '\0';
	*i += 1;
	free(line);
}

static	int	fill_map(int fd, char *config_file, t_config *config)
{
	int		elem_count;
	char	*line;
	int		i;

	fd = open(config_file, O_RDONLY);
	if (fd == -1 || prepare_map(fd, config) == -1)
		return (-1);
	elem_count = 0;
	line = get_next_line(fd);
	while (line && (elem_count < 6 || *line == '\n'))
	{
		if (*line != '\n' && elem_count != 6)
			elem_count++;
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		line_copy(line, config, &i);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	split_config(char *config_file, t_config *config)
{
	int	fd;

	fd = open(config_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Cannot open the config file\n"));
	if (fill_elems(fd, config) == -1)
	{
		close(fd);
		return (error_msg("Malloc failed\n"));
	}
	if (map_mesurer(fd, config) == -1)
		return (error_msg("Bad map size\n"));
	close(fd);
	if (config->x < 3 || config->y < 3)
		return (error_msg("Bad map size\n"));
	if (fill_map(fd, config_file, config) == -1)
		return (error_msg("Malloc failed\n"));
	trim_elems(config);
	sort_elems(config);
	return (0);
}
