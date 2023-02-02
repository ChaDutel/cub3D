/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:32:24 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/02 20:24:07 by charline         ###   ########.fr       */
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
		return (error_msg("Error : NULL parameter\n"));
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
		return (error_msg("Error : bad config name\n"));
	if (str[i] != '\0' || str[i - 1] != 'b' || str[i - 2] != 'u' \
		|| str[i - 3] != 'c' || str[i - 4] != '.')
		return (error_msg("Error : bad config name\n"));
	else
		return (0);
}

/* int	first_read(int fd)
{
	//6 incrementeurs, boucle check et augmemte
	i;
	str = str_cpy(line[i])
} */

int	parsing(char *config_file, t_config *config)
{
	(void)config;
	if (check_extension(config_file) == -1)
		return (-1);
	if (pre_parsing(config_file) == -1) //separate config and map //gnl
		return (-1);
	if (split_config(config_file, config) == -1)
		return (-1);
	// if (parse_elems(config) == -1)
	// 	return (-1);
	// if (parse_map(config) == -1)
	// 	return (-1);
	return (0);
}
