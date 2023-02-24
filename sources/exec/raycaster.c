/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/02/24 13:50:20 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int FixAng(int a)
{
	if(a > 359)
		a -= 360;
	if(a < 0)
		a += 360;
	return (a);
}

float degToRad(int a)
{
	return (a * PI / 180.0);
}

static	void	vertical_raycast(t_data *data, t_raymath *rc, t_point *v)
{
	rc->dof_counter = 0;
	rc->aTan = tan(degToRad(rc->ray.angle));
	if (cos(degToRad(rc->ray.angle)) > 0.001)
	{
		rc->ray.x = (((int)data->player.x / TEXTURE_SIZE) * TEXTURE_SIZE) + TEXTURE_SIZE;
		rc->ray.y = (data->player.x - rc->ray.x) * rc->aTan + data->player.y;
		rc->x_off = 64;
		rc->y_off = -rc->x_off * rc->aTan;
	}
	else if (cos(degToRad(rc->ray.angle)) < -0.001)
	{
		rc->ray.x = (((int)data->player.x / TEXTURE_SIZE) * TEXTURE_SIZE) - 0.0001;
		rc->ray.y = (data->player.x - rc->ray.x) * rc->aTan + data->player.y;
		rc->x_off = -TEXTURE_SIZE;
		rc->y_off = -rc->x_off * rc->aTan;
	}
	else
	{
		rc->ray.x = data->player.x;
		rc->ray.y = data->player.y;
		rc->dof_counter = 100;
	}


	while (rc->dof_counter < (int)data->config->x * 3 + 1) 
	{
		rc->elem_x = (int)(rc->ray.x) / TEXTURE_SIZE;
		rc->elem_y = (int)(rc->ray.y) / TEXTURE_SIZE;
		rc->elem_pos = rc->elem_y * data->config->x + rc->elem_x;
		if ((rc->elem_x <= (int)data->config->x - 1 && rc->elem_y <= (int)data->config->y -1 && rc->elem_x >= 0 && rc->elem_y >= 0) && data->config->map[rc->elem_y][rc->elem_x] == '1')
		{
			rc->distV = cos(degToRad(rc->ray.angle)) * (rc->ray.x - data->player.x) - sin(degToRad(rc->ray.angle)) * (rc->ray.y - data->player.y);
			break ;
		}
		else
		{
			rc->ray.x += rc->x_off;
			rc->ray.y += rc->y_off;
			rc->dof_counter += 1;
		}
	}
	v->x = rc->ray.x;
	v->y = rc->ray.y;
}

static	void	horizontal_raycast(t_data *data, t_raymath *rc, t_point *h)
{
	rc->dof_counter = 0;
	rc->aTan = 1.0 / rc->aTan;
	if (sin(degToRad(rc->ray.angle)) > 0.001)
	{
		rc->ray.y = (((int)data->player.y / TEXTURE_SIZE) * TEXTURE_SIZE) - 0.0001;
		rc->ray.x = (data->player.y - rc->ray.y) * rc->aTan + data->player.x;
		rc->y_off = -TEXTURE_SIZE;
		rc->x_off = -rc->y_off * rc->aTan;
	}
	else if (sin(degToRad(rc->ray.angle)) < -0.001)
	{
		rc->ray.y = (((int)data->player.y / TEXTURE_SIZE) * TEXTURE_SIZE) + TEXTURE_SIZE;
		rc->ray.x = (data->player.y - rc->ray.y) * rc->aTan + data->player.x;
		rc->y_off = TEXTURE_SIZE;
		rc->x_off = -rc->y_off * rc->aTan;
	}
	else
	{
		rc->ray.x = data->player.x;
		rc->ray.y = data->player.y;
		rc->dof_counter = 100;
	}

	
	while(rc->dof_counter < (int)data->config->y * 3 + 1)
	{
		rc->elem_x = (int)(rc->ray.x) / TEXTURE_SIZE;
		rc->elem_y = (int)(rc->ray.y) / TEXTURE_SIZE;
		rc->elem_pos = rc->elem_y * data->config->x + rc->elem_x;
		if((rc->elem_x <= (int)data->config->x - 1 && rc->elem_y <= (int)data->config->y -1 && rc->elem_x >= 0 && rc->elem_y >= 0) && data->config->map[rc->elem_y][rc->elem_x] == '1')
		{
			rc->distH = cos(degToRad(rc->ray.angle)) * (rc->ray.x - data->player.x) - sin(degToRad(rc->ray.angle)) * (rc->ray.y - data->player.y);
			break ;
		}
		else
		{
			rc->ray.x += rc->x_off;
			rc->ray.y += rc->y_off;
			rc->dof_counter += 1;
		}
	}
	h->x = rc->ray.x;
	h->y = rc->ray.y;
}

void	raycaster(t_data *data)
{
	t_raymath	rc;
	t_point		h;
	t_point		v;
	
	rc.distH = 999999;
	rc.distV = 999999;
	rc.nb_ray = 0;
	rc.ray.angle = FixAng(data->player.angle + 30);
	while (rc.nb_ray < 60)
	{
		vertical_raycast(data, &rc, &v);
		horizontal_raycast(data, &rc, &h);
		if (rc.distH > rc.distV)
		{
			rc.ray.x = v.x;
			rc.ray.y = v.y;
		}
		else
		{
			rc.ray.x = h.x;
			rc.ray.y = h.y;
		}
		bresenham_line(data, &rc);
		rc.ray.angle = FixAng(rc.ray.angle - 1.0);
		rc.nb_ray++;
	}
}
