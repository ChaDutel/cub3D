/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:24 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/01/25 17:27:55 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_extension(char *str)
{
	int	i;

	if (str == NULL)
		return (fatal_error("Error : NULL parameter\n"));
	while (str[i])
		i++;
	if (i < 5)
		return (fatal_error("Error : bad config name\n"));
	//if (str[i] == '\0' && str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c' && str[i - 4] == '.' && i == 4)
	if (str[i] != '\0' && str[i - 1] != 'b' && str[i - 2] != 'u' \
		&& str[i - 3] != 'c' && str[i - 4] != '.')
		return (fatal_error("Error : bad extension\n"));
	else
		return (0);
}

/* int	first_read(int fd)
{
	//6 incrementeurs, boucle check et augmemte
	i;
} */

int	parsing(char *config_file, t_config *config)
{
	int	fd;

	if (check_extension(config_file) == -1)
		return (-1);
	if (parse_elems(fd) == -1) //separate config and map //gnl
		return (-1);
	if (split_config(config_file, config) == -1)
		return (-1);
	if (parse_map(config) == -1)
		return (-1);
	return (0);
}
