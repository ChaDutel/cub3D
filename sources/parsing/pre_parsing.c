/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:42 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/05 12:28:28 by cdutel-l         ###   ########lyon.fr   */
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

/* int	check_elems(int fd, char *config_file)
{
	char		*line;
	static int	iter[6] = {0, 0, 0, 0, 0, 0};

	line = get_next_line(fd);
	check_coordinate()
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line != '\n')
		{
			if (find_coordinate(line, &iter) == -1)
			{
				free(line);
				return (-1);
			}
		}
		if (mini_check_coordinate(&iter) == 0)
			break;
	}
	if (check_nb_coordinate(iter) == -1)
	{
		free(line);
		return (-1);
	}
	if (!line)
		return (-1);
	check_map()
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (check_map(line) == -1)
		{
			free(line);
			return (-1);
		}
	}
	return (0);
} */

/* static int	find_coordinate(char *line, int *iter)
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
	{
		while (line[i])
		{
			if (line[i] != 'N' || line[i] != 'E' || line[i] != 'S' || line[i] != 'W' || line[i] != '0' || line[i] != '1')
				return (fatal_error("Error : wrong coordinate name\n"));
				// iter[7]++;
			i++;
		}
	}
	return (0);
	// else
	// 	return (fatal_error("Error : wrong coordinate name\n"));
	// return (0);
} */

//static char	coordinate[6][3] = {"NO\0", "EA\0", "SO\0", "WE\0", "F\0", "C\0"};
/* int	check_elems(int fd, char *config_file)
{
	char		*line;
	static int	iter[6] = {0, 0, 0, 0, 0, 0};

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line != '\n')
		{
			find_coordinate(line, &iter);
			// if (find_coordinate(line, &iter) == -1)
			// 	return (-1);
		}
	}
	if (check_nb_coordinate(iter) == -1)
		return (-1);
	return (0);
} */

/* int	check_elems(int fd, char *config_file)
{
	char		*line;
	static int	iter[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (iter[6] == 0)
		{
			if (line && line != '\n')
				find_coordinate(line, &iter);
		}
		else if (iter[6] != 0)
	}
	if (check_nb_coordinate(&iter) == -1)
		return (-1);
	return (0);
} */
