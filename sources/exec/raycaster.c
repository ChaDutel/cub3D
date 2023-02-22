/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/02/22 08:31:51 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	void	check_horizontal_line(t_data *data, t_raymath *rc)
{
	if (rc->ray.angle < PI)
	{
		rc->ray.y = roundint((int)data->player.y) - 0.0001;
		rc->ray.x = (data->player.y - rc->ray.y) * rc->aTan + data->player.x;
		rc->y_off = -TEXTURE_SIZE;
		rc->x_off = -rc->y_off * rc->aTan;
	}
	else if (rc->ray.angle > PI)
	{
		rc->ray.y = roundint((int)data->player.y) + TEXTURE_SIZE;
		rc->ray.x = (data->player.y - rc->ray.y) * rc->aTan + data->player.x;
		rc->y_off = TEXTURE_SIZE;
		rc->x_off = -1 * rc->y_off * rc->aTan;
	}
	else
	{
		rc->ray.x = data->player.x;
		rc->ray.y = data->player.y;
		rc->dof_counter = data->config->y;
	}
}

// static	void	check_vertical_line()
// {
	
// }

void	raycaster(t_data *data)
{
	t_raymath	rc;
	
	rc.ray.angle = data->player.angle;
	rc.nb_ray = 0;
	while (rc.nb_ray < 1) //USE FOV INSTEAD OF ONE for example
	{
		rc.dof_counter = 0;
		rc.aTan = -1.0 / tan(rc.ray.angle);
		check_horizontal_line(data, &rc);
		while (rc.dof_counter < (int)data->config->y && rc.dof_counter < MAX_DOF)
		{
			rc.elem_x = (int)rc.ray.x / TEXTURE_SIZE;
			rc.elem_y = (int)rc.ray.y / TEXTURE_SIZE;
			rc.elem_pos = rc.elem_y * data->config->x + rc.elem_x;
			if (rc.elem_pos < (int)data->config->x * (int)data->config->y
				&& data->config->map[rc.elem_y][rc.elem_x] == '1')
					rc.dof_counter = MAX_DOF;
			else
			{
				rc.ray.x += rc.x_off;
				rc.ray.y += rc.y_off;
				rc.dof_counter++;
			}
		}
		// check_vertical_line();
		bresenham_line(data, &rc);
		rc.nb_ray++;
	}
}
