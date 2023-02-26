/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:31:41 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/26 15:51:20 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	mini_dir_up(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = -sin(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.x;
	new_y = -cos(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->mini_player.x = new_x;
		data->mini_player.y = new_y;
	}
}

void	mini_dir_down(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = sin(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.x;
	new_y = cos(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->mini_player.x = new_x;
		data->mini_player.y = new_y;
	}
}

void	mini_dir_left(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = cos(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.x;
	new_y = -sin(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->mini_player.x = new_x;
		data->mini_player.y = new_y;
	}
}

void	mini_dir_right(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = -cos(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.x;
	new_y = sin(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.y;
	if (data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x \
		/ TEXTURE_SIZE] != '1')
	{
		data->mini_player.x = new_x;
		data->mini_player.y = new_y;
	}
}
