/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:35:41 by maxperei          #+#    #+#             */
/*   Updated: 2023/03/01 00:29:22 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dir_right(t_data *data)
{
	float	new_x;
	float	new_y;

	mini_dir_right(data);
	new_x = -sin(deg_to_rad(data->player.angle)) * 4 + data->player.x;
	new_y = cos(deg_to_rad(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	dir_left(t_data *data)
{
	float	new_x;
	float	new_y;

	mini_dir_left(data);
	new_x = sin(deg_to_rad(data->player.angle)) * 4 + data->player.x;
	new_y = -cos(deg_to_rad(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	dir_down(t_data *data)
{
	float	new_x;
	float	new_y;

	mini_dir_down(data);
	new_x = cos(deg_to_rad(data->player.angle)) * 4 + data->player.x;
	new_y = sin(deg_to_rad(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	dir_up(t_data *data)
{
	float	new_x;
	float	new_y;

	mini_dir_up(data);
	new_x = -cos(deg_to_rad(data->player.angle)) * 4 + data->player.x;
	new_y = -sin(deg_to_rad(data->player.angle)) * 4 + data->player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}
