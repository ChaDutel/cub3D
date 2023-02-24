/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/02/24 09:43:38 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	int FixAng(int a)
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
		rc->ray.x = (((int)data->player.x >> 6) << 6) + 64;
		rc->ray.y = (data->player.x - rc->ray.x) * rc->aTan + data->player.y;
		rc->x_off = 64;
		rc->y_off = -rc->x_off * rc->aTan;
	}
	else if (cos(degToRad(rc->ray.angle)) < -0.001)
	{
		rc->ray.x = (((int)data->player.x >> 6) << 6) - 0.0001;
		rc->ray.y = (data->player.x - rc->ray.x) * rc->aTan + data->player.y;
		rc->x_off = -64;
		rc->y_off = -rc->x_off * rc->aTan;
	}
	else
	{
		rc->ray.x = data->player.x;
		rc->ray.y = data->player.y;
		rc->dof_counter = 8;
	}


	while (rc->dof_counter < 8) 
	{
		rc->elem_x = (int)(rc->ray.x) >> 6;
		rc->elem_y = (int)(rc->ray.y) >> 6;
		// if (rc->elem_x > (int)data->config->x - 1 || rc->elem_y > (int)data->config->y -1)
		// {
		// 	rc->ray.x = data->player.x;
		// 	rc->ray.y = data->player.y;
		// 	break ;
		// }
		rc->elem_pos = rc->elem_y * data->config->x + rc->elem_x;
		if ((rc->elem_x <= (int)data->config->x - 1 && rc->elem_y <= (int)data->config->y -1 && rc->elem_x >= 0 && rc->elem_y >= 0) && data->config->map[rc->elem_y][rc->elem_x] == '1')
		{
			rc->dof_counter = 8;
			rc->distV = cos(degToRad(rc->ray.angle)) * (rc->ray.x - data->player.x) - sin(degToRad(rc->ray.angle)) * (rc->ray.y - data->player.y);
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
		rc->ray.y = (((int)data->player.y >> 6) << 6) - 0.0001;
		rc->ray.x = (data->player.y - rc->ray.y) * rc->aTan + data->player.x;
		rc->y_off = -64;
		rc->x_off = -rc->y_off * rc->aTan;
	}
	else if (sin(degToRad(rc->ray.angle)) < -0.001)
	{
		rc->ray.y = (((int)data->player.y >> 6) << 6) + 64;
		rc->ray.x = (data->player.y - rc->ray.y) * rc->aTan + data->player.x;
		rc->y_off = 64;
		rc->x_off = -rc->y_off * rc->aTan;
	}
	else
	{
		rc->ray.x = data->player.x;
		rc->ray.y = data->player.y;
		rc->dof_counter = 8;
	}

	
	while(rc->dof_counter < 8)
	{
		rc->elem_x = (int)(rc->ray.x) >> 6;
		rc->elem_y = (int)(rc->ray.y) >> 6;
		// if (rc->elem_x > (int)data->config->x - 1 || rc->elem_y > (int)data->config->y -1)
		// {
		// 	rc->ray.x = data->player.x;
		// 	rc->ray.y = data->player.y;
		// 	break ;
		// }
		rc->elem_pos = rc->elem_y * data->config->x + rc->elem_x;
		if((rc->elem_x <= (int)data->config->x - 1 && rc->elem_y <= (int)data->config->y -1 && rc->elem_x >= 0 && rc->elem_y >= 0) && data->config->map[rc->elem_y][rc->elem_x] == '1')
		{
			rc->dof_counter = 8;
			rc->distH = cos(degToRad(rc->ray.angle)) * (rc->ray.x - data->player.x) - sin(degToRad(rc->ray.angle)) * (rc->ray.y - data->player.y);
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
	rc.ray.angle = FixAng(data->player.angle);
	while (rc.nb_ray < 1)
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
		rc.ray.angle = FixAng(rc.ray.angle - 1);
		rc.nb_ray++;
	}
}

/* float	find_ray_len(t_vector player, t_vector ray)
{
	return (sqrt((ray.x - player.x) * (ray.x - player.x)
		+ (ray.y - player.y) * (ray.y - player.y)));
}

static	void	check_horizontal_line(t_data *data, t_raymath *rc)
{
	if (rc->ray.angle == 0 || rc->ray.angle == PI)
	{
		rc->ray.x = data->player.x;
		rc->ray.y = data->player.y;
		rc->dof_counter = data->config->y;
	}
	else if (rc->ray.angle < PI)
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
}

static	void	check_vertical_line(t_data *data, t_raymath *rc)
{
	if (rc->ray.angle == 0 || rc->ray.angle == PI)
	{
		rc->ray.x = data->player.x;
		rc->ray.y = data->player.y;
		rc->dof_counter = data->config->y;
	}
	else if (rc->ray.angle > (PI / 2) && rc->ray.angle < ((3 * PI) / 2))
	{
		rc->ray.x = roundint((int)data->player.x) - 0.0001;
		rc->ray.y = (data->player.x - rc->ray.x) * rc->aTan + data->player.y;
		rc->x_off = -TEXTURE_SIZE;
		rc->y_off = -rc->x_off * rc->aTan;
	}
	else if (rc->ray.angle < (PI / 2) || rc->ray.angle > ((3 * PI) / 2) )
	{
		rc->ray.x = roundint((int)data->player.x) + TEXTURE_SIZE;
		rc->ray.y = (data->player.x - rc->ray.x) * rc->aTan + data->player.y;
		rc->x_off = TEXTURE_SIZE;
		rc->y_off = -rc->x_off * rc->aTan;
	}
}

static	int	check_ray_limits(t_data *data, t_raymath *rc)
{
	if (rc->elem_x < 0)
		rc->elem_x = 1;
	else if (rc->elem_x > (int)data->config->x)
		rc->elem_x = data->config->x - 2;
	if (rc->elem_y < 0)
		rc->elem_y = 1;
	else if (rc->elem_y > (int)data->config->y)
		rc->elem_y = data->config->y - 2;
	if (rc->elem_x == 1 || rc->elem_x == (int)data->config->x
		|| rc->elem_y == 1 || rc->elem_y == (int)data->config->y)
		return (-1);
	else
		return (0);
}

static	void	horizontal_cast(t_data *data, t_raymath *rc, t_point *h)
{
	rc->dof_counter = 0;
	rc->aTan = -1.0 / tan(rc->ray.angle);
	check_horizontal_line(data, rc);
	while (rc->dof_counter < (int)data->config->y && rc->dof_counter < MAX_DOF)
	{
		rc->elem_x = (int)rc->ray.x / TEXTURE_SIZE;
		rc->elem_y = (int)rc->ray.y / TEXTURE_SIZE;
		if (check_ray_limits(data, rc) == -1)
			break ;
		rc->elem_pos = rc->elem_y * data->config->x + rc->elem_x;
		if (rc->elem_pos > 0 && rc->elem_pos < (int)data->config->x * (int)data->config->y
			&& data->config->map[rc->elem_y][rc->elem_x] == '1')
			{
				h->x = rc->ray.x;
				h->y = rc->ray.y;
				rc->distH = find_ray_len(data->player, rc->ray);
				rc->dof_counter = MAX_DOF;
			}
		else
		{
			rc->ray.x += rc->x_off;
			rc->ray.y += rc->y_off;
			rc->dof_counter++;
		}
	}
}

static	void	vertical_cast(t_data *data, t_raymath *rc, t_point *v)
{
	rc->dof_counter = 0;
	rc->aTan = -tan(rc->ray.angle);
	check_vertical_line(data, rc);
	while (rc->dof_counter < (int)data->config->y && rc->dof_counter < MAX_DOF)
	{
		rc->elem_x = (int)rc->ray.x / TEXTURE_SIZE;
		rc->elem_y = (int)rc->ray.y / TEXTURE_SIZE;
		if (check_ray_limits(data, rc) == -1)
			break ;
		rc->elem_pos = rc->elem_y * data->config->x + rc->elem_x;
		if (rc->elem_pos > 0 && rc->elem_pos < (int)data->config->x * (int)data->config->y
			&& data->config->map[rc->elem_y][rc->elem_x] == '1')
			{
				v->x = rc->ray.x;
				v->y = rc->ray.y;
				rc->distV = find_ray_len(data->player, rc->ray);
				rc->dof_counter = MAX_DOF;
			}
		else
		{
			rc->ray.x += rc->x_off;
			rc->ray.y += rc->y_off;
			rc->dof_counter++;
		}
	}
}

void	raycaster(t_data *data)
{
	t_raymath	rc;
	t_point		h;
	t_point		v;
	
	rc.distH = 1000000;
	h.x = data->player.x;
	h.y = data->player.y;
	rc.distV = 1000000;
	v.x = data->player.x;
	v.y = data->player.y;
	rc.ray.angle = data->player.angle;
	rc.nb_ray = 0;
	while (rc.nb_ray < 1) //USE FOV and screen width INSTEAD 
	{
		horizontal_cast(data, &rc, &h);
		vertical_cast(data, &rc, &v);
		if (rc.distH < rc.distV)
		{
			rc.ray.x = h.x;
			rc.ray.y = h.y;
		}
		else
		{
			rc.ray.x = v.x;
			rc.ray.y = v.y;
		}
		bresenham_line(data, &rc);
		rc.nb_ray++;
	}
}
 */