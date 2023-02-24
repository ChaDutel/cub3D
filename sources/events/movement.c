/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:35:41 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/24 19:27:10 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

double degToRad_float(float a)
{
	return ((double)a * PI / 180.0);
}

void	new_direction_right(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	// new_x = sin(degToRad_float(data->player.angle)) * 10.0f + data->player.x;
	// new_y = cos(degToRad_float(data->player.angle)) * 10.0f + data->player.y;
	new_x = sin(degToRad_float(data->player.angle)) * 4 + data->player.x;
	new_y = cos(degToRad_float(data->player.angle)) * 4 + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_left(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	// new_x = -sin(degToRad_float(data->player.angle)) * 10.0f + data->player.x;
	// new_y = -cos(degToRad_float(data->player.angle)) * 10.0f + data->player.y;
	new_x = -sin(degToRad_float(data->player.angle)) * 4 + data->player.x;
	new_y = -cos(degToRad_float(data->player.angle)) * 4 + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_down(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = -cos(degToRad_float(data->player.angle)) * 4 + data->player.x;
	new_y = sin(degToRad_float(data->player.angle)) * 4 + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_up(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = cos(degToRad_float(data->player.angle)) * 4 + data->player.x;
	new_y = -sin(degToRad_float(data->player.angle)) * 4 + data->player.y;
	// Collision test if(data->config->map[Math.floor(new_y)][Math.floor(new_x)] == 0)
    if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}