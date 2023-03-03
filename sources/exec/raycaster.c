/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/03/03 12:35:28 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_texture_color(t_data *data, t_raycast *rc, int height, int texture_type)
{
	char	*pixel;
	int		color;
	int		tex_y;
	int		tex_x;

	if (rc->wall_dist == 0)
		rc->wall_height = WINDOW_HEIGHT;
	else
		rc->wall_height = WINDOW_HEIGHT / rc->wall_dist;
	tex_y = (int)(height * data->tex[texture_type].height / rc->wall_height)
		% data->tex[texture_type].height * data->tex[texture_type].line_len;
	if (texture_type == SO || texture_type == WE)
		tex_x = ((int)((1.0f - rc->wall_percent)
					* data->tex[texture_type].width));
	else
		tex_x = ((int)(rc->wall_percent * data->tex[texture_type].width));
	tex_x *= (data->tex[texture_type].bpp / 8);
	pixel = data->tex[texture_type].addr + tex_y + tex_x;
	color = *(int *)pixel;
	return (color);
}

int	find_texture_type(t_raycast *rc)
{
	if (rc->side == 0)
	{
		if (rc->v.y > 0)
			return (SO);
		return (NO);
	}
	else
	{
		if (rc->v.x > 0)
			return (EA);
		else
			return (WE);
	}
}

static	void	throw_ray(t_data *data, t_raycast *rc)
{
	int	i;

	i = 0;
	while (i < MAX_DOF)
	{
		if (rc->t_max_x < rc->t_max_y)
		{
			rc->side = 1;
			rc->t_max_x += rc->t_delta_x;
			rc->pos.x += rc->step_x;
		}
		else
		{
			rc->side = 0;
			rc->t_max_y += rc->t_delta_y;
			rc->pos.y += rc->step_y;
		}
		rc->elem.x = floor(rc->pos.x);
		rc->elem.y = floor(rc->pos.y);
		if (rc->elem.x >= 0 && rc->elem.x < (int)data->config->x
			&& rc->elem.y >= 0 && rc->elem.y < (int)data->config->y
			&& data->config->map[(int)rc->elem.y][(int)rc->elem.x] == '1')
			break ;
		i++;
	}
}

void	find_axe(t_raycast *rc)
{
	if (rc->v.x > 0)
		rc->step_x = 1;
	else
		rc->step_x = -1;
	if (rc->v.y > 0)
		rc->step_y = 1;
	else
		rc->step_y = -1;
}

void	raycaster(t_data *data)
{
	t_raycast	rc;

	rc.nb_ray = 0;
	rc.ray_angle = fix_ang(data->player.angle + ((float)FOV / 2.0));
	rc.angle_step = (float)FOV / (float)WINDOW_WIDTH;
	while (rc.nb_ray < WINDOW_WIDTH)
	{
		rc.pos.x = data->player.x;
		rc.pos.y = data->player.y;
		rc.u.x = rc.pos.x;
		rc.u.y = rc.pos.y;
		rc.v.x = cos(deg_to_rad(rc.ray_angle));
		rc.v.y = -sin(deg_to_rad(rc.ray_angle));
		find_axe(&rc);
		rc.t_delta_x = 1 / fabs(rc.v.x);
		rc.t_delta_y = 1 / fabs(rc.v.y);
		rc.t_max_x = get_t_max_x(&rc);
		rc.t_max_y = get_t_max_y(&rc);
		throw_ray(data, &rc);
		choose_dist(data, &rc);
		draw_image(data, &rc);
		rc.nb_ray++;
		rc.ray_angle = fix_ang(rc.ray_angle - rc.angle_step);
	}
}
