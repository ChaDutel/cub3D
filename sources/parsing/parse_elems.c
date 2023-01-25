/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:42 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/01/25 19:58:03 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	check_nb_coordinate(int *iter)
{
	int	i;

	i = 0;
	while (iter[i])
	{
		if (iter[i] > 1)
			return (fatal_error("Error : duplicate coordinate\n"));
		else if (iter[i] < 1)
			return (fatal_error("Error : coordinate missing\n"));
		i++;
	}
	return (0);
}

static void	find_coordinate(char *line, int *iter)
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
	/* else
		return (fatal_error("Error : wrong coordinate name\n"));
	return (0); */
}

//static char	coordinate[6][3] = {"NO\0", "EA\0", "SO\0", "WE\0", "F\0", "C\0"};
int	check_elems(int fd, char *config_file)
{
	char		*line;
	static int	iter[6] = {0, 0, 0, 0, 0, 0};

	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		if (line != '\n' && line != '\0')
		{
			find_coordinate(line, &iter);
			// if (find_coordinate(line, &iter) == -1)
			// 	return (-1);
		}
		free(line);
	}
	if (check_nb_coordinate(iter) == -1)
		return (-1);
	return (0);
}

int	parse_elems(char *config_file)
{
	int	fd;

	fd = open(config_file, O_RDONLY);
	if (fd == -1)
		return (normal_error("Error : can't open the config file\n"));
	if (check_elems(fd, config_file) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
