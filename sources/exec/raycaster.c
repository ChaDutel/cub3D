/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/03/01 10:00:52 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	void	draw_floor(t_data *data, int x, int start, int stop)
{
	int	color;

	color = (data->config->colors[FLOOR][R] << 16)
		+ (data->config->colors[FLOOR][G] << 8)
		+ data->config->colors[FLOOR][B];
	while (start < stop)
	{
		image_pixel_put(data, x, start, color);
		start++;
	}
}

static	void	draw_ceilling(t_data *data, int x, int start, int stop)
{
	int	color;

	color = (data->config->colors[CEIL][R] << 16)
		+ (data->config->colors[CEIL][G] << 8)
		+ data->config->colors[CEIL][B];
	while (start < stop)
	{
		image_pixel_put(data, x, start, color);
		start++;
	}
}

static	void	draw_image(t_data *data, t_raycast *rc)
{
	int	wall_height;
	// float	distance;

	// distance = sqrt(pow(data->player_pos.x - rc->t_max_x, 2)
	// 		+ pow(data->player_pos.y - rc->t_max_y, 2));

	wall_height = floor((WINDOW_HEIGHT) / 2 / rc->wall_dist);
	draw_floor(data, rc->nb_ray, WINDOW_HEIGHT / 2 + wall_height, WINDOW_HEIGHT - 1);
	draw_ceilling(data, rc->nb_ray, 0, WINDOW_HEIGHT / 2 - wall_height);
}

static	void	choose_dist(t_data *data, t_raycast * rc)
{
	if (rc->side == 1)
	{
		rc->wall_dist = rc->t_max_x - rc->t_delta_x;
		rc->wall_percent = rc->u.y + rc->v.y * rc->wall_dist;
	}
	else
	{
		rc->wall_dist = rc->t_max_y - rc->t_delta_y;
		rc->wall_percent = rc->u.x + rc->v.x * rc->wall_dist;
	}
	rc->wall_dist *= cos(deg_to_rad(fix_ang(rc->ray_angle - data->player.angle)));
	//printf("wall_dist %f\n", rc->wall_dist);
	//rc->wall_percent -= floor(rc->wall_percent);
	
}

static	float	get_t_max_x(t_raycast *rc)
{
	if (rc->v.x < 0)
		return (rc->pos.x - floor(rc->u.x)) * rc->t_delta_x;
	else
		return (floor(rc->u.x) + 1.0f - rc->pos.x) * rc->t_delta_x;
}

static	float	get_t_max_y(t_raycast *rc)
{
	if (rc->v.y < 0)
		return (rc->pos.y - rc->u.y) * rc->t_delta_y;
	else
		return (rc->u.y + 1.0f - rc->pos.y) * rc->t_delta_y;
}

void	raycaster(t_data *data)
{
	t_raycast	rc;
	int			i;

	rc.nb_ray = 0;
	rc.ray_angle = fix_ang(data->player.angle + ((float)FOV / 2.0));
	rc.angle_step = (float)FOV / (float)WINDOW_WIDTH;	
	while (rc.nb_ray < WINDOW_WIDTH)
	{
		rc.pos.x = data->player_pos.x;
		rc.pos.y = data->player_pos.y;
		rc.u.x = rc.pos.x;
		rc.u.y = rc.pos.y;
		rc.v.x = cos(deg_to_rad(rc.ray_angle));
		rc.v.y = sin(deg_to_rad(rc.ray_angle));

		if (rc.v.x > 0)
			rc.step_x = 1;
		else
			rc.step_x = -1;

		if (rc.v.y > 0)
			rc.step_y = 1;
		else
			rc.step_y = -1;
		

		rc.t_delta_x = 1 / fabs(rc.v.x);
		rc.t_delta_y = 1 / fabs(rc.v.y);

		rc.t_max_x = get_t_max_x(&rc);
		rc.t_max_y = get_t_max_y(&rc);

		i = 0;
		while (i < MAX_DOF)
		{
			if (rc.t_max_x < rc.t_max_y)
			{
				rc.side = 1;
				rc.t_max_x += rc.t_delta_x;
				rc.pos.x += rc.step_x; 
			}
			else
			{
				rc.side = 0;
				rc.t_max_y += rc.t_delta_y;
				rc.pos.y += rc.step_y;
			}
			rc.elem.x = (int)rc.pos.x;
			rc.elem.y = (int)rc.pos.y;
			if (rc.elem.x >= 0 && rc.elem.x < (int)data->config->x
				&& rc.elem.y >= 0 && rc.elem.y < (int)data->config->y
				&& data->config->map[(int)rc.elem.y][(int)rc.elem.x] == '1')
				break ;
			i++;
		}
		choose_dist(data, &rc);
		draw_image(data, &rc);
		rc.nb_ray++;
		rc.ray_angle -= fix_ang(rc.angle_step);
	}
}
