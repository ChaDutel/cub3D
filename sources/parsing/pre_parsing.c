/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:42 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/19 10:12:03 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	check_coordinate(int fd, char *line)
{
	static int	iter[6] = {0, 0, 0, 0, 0, 0};

	while (line)
	{
		if (line && *line != '\n')
		{
			if (find_coordinate(line, iter) == -1)
			{
				free(line);
				return (-1);
			}
		}
		if (mini_check_coordinate(iter) == 0)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (check_nb_coordinate(iter) == -1)
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}

static int	check_map(int fd, char *line)
{
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line)
	{
		if (check_map_elems(line) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

static int	check_elems(int fd)
{
	char		*line;

	line = get_next_line(fd);
	if (check_coordinate(fd, line) == -1)
		return (-1);
	if (check_map(fd, line) == -1)
		return (-1);
	return (0);
}

int	pre_parsing(char *config_file)
{
	int	fd;

	fd = open(config_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Error : can't open the config file\n"));
	if (check_elems(fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
