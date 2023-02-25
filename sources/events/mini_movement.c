/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:31:41 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/25 12:46:49 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

double	degtorad_float(float a)
{
	return ((double)a * PI / 180.0);
}

void	new_direction_right(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = -sin(degtorad_float(data->player.angle)) * 4 + data->player.x;
	new_y = cos(degtorad_float(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_left(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = sin(degtorad_float(data->player.angle)) * 4 + data->player.x;
	new_y = -cos(degtorad_float(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_down(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = cos(degtorad_float(data->player.angle)) * 4 + data->player.x;
	new_y = sin(degtorad_float(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_up(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = -cos(degtorad_float(data->player.angle)) * 4 + data->player.x;
	new_y = -sin(degtorad_float(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}
