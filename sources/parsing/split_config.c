/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:32:54 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/01/25 19:14:28 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	int	fill_elems(int fd, t_config *config)
{
	int		elem_count;
	char	*line;

	config->elems = malloc(sizeof(char *) * 7);
	if (!config->elems)
		return (-1);
	config->elems[6] = NULL;
	elem_count = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (elem_count != 6)
	{
		
	}
}

int	split_config(char *config_file, t_config *config)
{
	int	fd;

	fd = open(config_file, O_RDONLY);
	if (fd == -1)
		return (normal_error("Error : can't open the config file\n"));
	if (fill_elems(fd, config) == -1)
		return (fatal_error("Error : malloc failed\n"));
	// fill_map()
	close(fd);
	return (0);
}