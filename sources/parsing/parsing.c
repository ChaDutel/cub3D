/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:24 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/03 16:27:12 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	int	check_extension(char *str)
{
	int	i;
	int	j;
	int	u;

	i = 0;
	u = 0;
	if (str == NULL)
		return (error_msg("NULL parameter\n"));
	while (str[i])
		i++;
	j = i;
	while (j != 0 && str[j] != '/')
	{
		u++;
		j--;
	}
	u--;
	if (u < 5)
		return (error_msg("Bad config\n"));
	if (str[i] != '\0' || str[i - 1] != 'b' || str[i - 2] != 'u' \
		|| str[i - 3] != 'c' || str[i - 4] != '.')
		return (error_msg("Bad config\n"));
	else
		return (0);
}

static	int	is_folder(char *config_file)
{
	int	fd;

	fd = open(config_file, __O_DIRECTORY);
	if (fd == -1)
		return (0);
	else
	{
		close(fd);
		return (error_msg("The map is a repertory\n"));
	}
}

int	parsing(char *config_file, t_config *config)
{
	if (is_folder(config_file) == -1)
		return (-1);
	if (check_extension(config_file) == -1)
		return (-1);
	if (pre_parsing(config_file) == -1)
		return (-1);
	if (split_config(config_file, config) == -1)
		return (-1);
	if (parse_elems(config) == -1)
		return (-1);
	if (parse_map(config) == -1)
		return (-1);
	return (0);
}
