/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:05 by charline          #+#    #+#             */
/*   Updated: 2023/02/27 17:56:17 by maxperei         ###   ########lyon.fr   */
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
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	if (data->tex[NO].mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->tex[NO].mlx_img);
	if (data->tex[SO].mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->tex[SO].mlx_img);
	if (data->tex[EA].mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->tex[EA].mlx_img);
	if (data->tex[WE].mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->tex[WE].mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (-1);
}
