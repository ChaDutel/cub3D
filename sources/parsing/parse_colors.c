/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:50:43 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/01 00:27:07 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	tab_and_check_max_min(t_config *config
	, char *str, int iter, int i)
{
	int	values;

	values = ft_atoi(str);
	if (values > 255)
		return (error_msg("Colors values are too big\n"));
	else if (values < 0)
		return (error_msg("Colors values are too small\n"));
	config->colors[i][iter] = values;
	return (0);
}

static int	check_separation(char c, char *str, int nb_values, int *j)
{
	if (nb_values != 2 && c != ',')
	{
		free(str);
		return (error_msg("Wrong colors values\n"));
	}
	else if (nb_values == 2 && c != '\0')
	{
		free(str);
		return (error_msg("Wrong last color values\n"));
	}
	*j += 1;
	return (0);
}

static char	*create_str_num(t_config *config, int i, int *j)
{
	char	*str;
	char	*str_tmp;

	str = NULL;
	while (config->elems[i][*j] && (config->elems[i][*j] >= '0'
		&& config->elems[i][*j] <= '9'))
	{
		str_tmp = str;
		str = char_join(str_tmp, config->elems[i][*j]);
		if (!str)
		{
			free(str_tmp);
			error_msg("Malloc failed\n");
			return (NULL);
		}
		free(str_tmp);
		if (ft_strlen(str) > 3)
		{
			free(str);
			error_msg("Color values are too big\n");
			return (NULL);
		}
		*j += 1;
	}
	return (str);
}

static int	check_num(t_config *config, int i, int *j)
{
	while (config->elems[i][*j] && config->elems[i][*j] == ' ')
		*j += 1;
	if (config->elems[i][*j] < '0' || config->elems[i][*j] > '9')
		return (error_msg("Wrong colors values\n"));
	return (0);
}

int	check_colors_values(t_config *config, int i, int j)
{
	int		nb_values;
	char	*str;

	nb_values = 0;
	while (nb_values < 3)
	{
		if (check_num(config, i, &j) == -1)
			return (-1);
		str = create_str_num(config, i, &j);
		if (str == NULL)
			return (-1);
		while (config->elems[i][j] && nb_values != 2
			&& config->elems[i][j] == ' ')
			j++;
		if (check_separation(config->elems[i][j], str, nb_values, &j) == -1)
			return (-1);
		if (tab_and_check_max_min(config, str, nb_values, i - 4) == -1)
		{
			free(str);
			return (-1);
		}
		free(str);
		nb_values++;
	}
	return (0);
}
