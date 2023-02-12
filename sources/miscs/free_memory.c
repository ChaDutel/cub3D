/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:05 by charline          #+#    #+#             */
/*   Updated: 2023/02/12 10:52:11 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	if (config->elems)
	{
		while (config->elems[i])
		{
			free(config->elems[i]);
			i++;
		}
		free(config->elems);
	}
	i = 0;
	if (config->map)
	{
		while (config->map[i])
		{
			free(config->map[i]);
			i++;
		}
		free(config->map);
	}
	config->elems = NULL;
	config->map = NULL;
}

int	free_mlx(t_data *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (-1);
}