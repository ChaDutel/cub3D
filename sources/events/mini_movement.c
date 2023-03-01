/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:31:41 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/01 14:52:30 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	mini_dir_up(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = -sin(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.x;
	new_y = -cos(deg_to_rad(data->mini_player.angle)) * 4 + data->mini_player.y;
	if (new_x >= data->config->x || new_x < 0 || new_y >= data->config->y || new_y < 0)
        return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
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
	if (new_x >= data->config->x || new_x < 0 || new_y >= data->config->y || new_y < 0)
        return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
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
	if (new_x >= data->config->x || new_x < 0 || new_y >= data->config->y || new_y < 0)
        return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
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
	if (new_x >= data->config->x || new_x < 0 || new_y >= data->config->y || new_y < 0)
        return ;
	if (data->config->map[(int)new_y][(int)new_x] != '1')
	{
		data->mini_player.x = new_x;
		data->mini_player.y = new_y;
	}
}
