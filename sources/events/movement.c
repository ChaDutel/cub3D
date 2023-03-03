/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:35:41 by maxperei          #+#    #+#             */
/*   Updated: 2023/03/03 14:53:57 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	check_wall_next_step(t_data *data, float new_x,
			float new_y, t_dir next)
{
	if ((int)new_x >= (int)data->config->x || (int)new_x < 0 \
		|| (int)new_y >= (int)data->config->y || (int)new_y < 0 \
		|| (int)next.x >= (int)data->config->x || (int)next.x < 0 \
		|| (int)next.y >= (int)data->config->y || (int)next.y < 0)
		return ;
	if ((data->config->map[(int)new_y][(int)new_x] == '0' \
		|| data->config->map[(int)new_y][(int)new_x] == 'N'\
		|| data->config->map[(int)new_y][(int)new_x] == 'E'\
		|| data->config->map[(int)new_y][(int)new_x] == 'S'\
		|| data->config->map[(int)new_y][(int)new_x] == 'W')
		&& (data->config->map[(int)next.y][(int)next.x] == '0' \
		|| data->config->map[(int)next.y][(int)next.x] == 'N'\
		|| data->config->map[(int)next.y][(int)next.x] == 'E'\
		|| data->config->map[(int)next.y][(int)next.x] == 'S'\
		|| data->config->map[(int)next.y][(int)next.x] == 'W'))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	dir_left(t_data *data)
{
	float	new_x;
	float	new_y;
	t_dir	next;

	new_x = -sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = -cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	next.x = -sin(deg_to_rad(data->player.angle)) * 0.25f + new_x;
	next.y = -cos(deg_to_rad(data->player.angle)) * 0.25f + new_y;
	check_wall_next_step(data, new_x, new_y, next);
}

void	dir_right(t_data *data)
{
	float	new_x;
	float	new_y;
	t_dir	next;

	new_x = sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	next.x = sin(deg_to_rad(data->player.angle)) * 0.25f + new_x;
	next.y = cos(deg_to_rad(data->player.angle)) * 0.25f + new_y;
	check_wall_next_step(data, new_x, new_y, next);
}

void	dir_down(t_data *data)
{
	float	new_x;
	float	new_y;
	t_dir	next;

	new_x = -cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	next.x = -cos(deg_to_rad(data->player.angle)) * 0.25f + new_x;
	next.y = sin(deg_to_rad(data->player.angle)) * 0.25f + new_y;
	check_wall_next_step(data, new_x, new_y, next);
}

void	dir_up(t_data *data)
{
	float	new_x;
	float	new_y;
	t_dir	next;

	new_x = cos(deg_to_rad(data->player.angle)) * 0.25f + data->player.x;
	new_y = -sin(deg_to_rad(data->player.angle)) * 0.25f + data->player.y;
	next.x = cos(deg_to_rad(data->player.angle)) * 0.25f + new_x;
	next.y = -sin(deg_to_rad(data->player.angle)) * 0.25f + new_y;
	check_wall_next_step(data, new_x, new_y, next);
}
