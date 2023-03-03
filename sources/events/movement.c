/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:35:41 by maxperei          #+#    #+#             */
/*   Updated: 2023/03/03 10:33:27 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dir_left(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = -sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = -cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	if ((int)new_x >= (int)data->config->x || (int)new_x < 0 \
		|| (int)new_y >= (int)data->config->y || (int)new_y < 0)
		return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	dir_right(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	if ((int)new_x >= (int)data->config->x || (int)new_x < 0 \
		|| (int)new_y >= (int)data->config->y || (int)new_y < 0)
		return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	dir_down(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = -cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	if ((int)new_x >= (int)data->config->x || (int)new_x < 0 \
		|| (int)new_y >= (int)data->config->y || (int)new_y < 0)
		return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	dir_up(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = -sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	if ((int)new_x >= (int)data->config->x || (int)new_x < 0 \
		|| (int)new_y >= (int)data->config->y || (int)new_y < 0)
		return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}
