/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:05 by charline          #+#    #+#             */
/*   Updated: 2023/02/17 15:38:48 by cdutel-l         ###   ########lyon.fr   */
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

/*
		before when mlx_img was in : data.img->mlx_img, but it made leaks
int	free_mlx(t_data *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->img && data->img->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (-1);
} */

int	free_mlx(t_data *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->img && data->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (-1);
}