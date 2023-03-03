/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:33:27 by maxperei          #+#    #+#             */
/*   Updated: 2023/03/03 12:36:01 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	choose_dist(t_data *data, t_raycast *rc)
{
	(void)data;
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
	rc->wall_dist *= cos(deg_to_rad(fix_ang(rc->ray_angle \
			- data->player.angle)));
	rc->wall_percent -= floor(rc->wall_percent);
}

float	get_t_max_x(t_raycast *rc)
{
	if (rc->v.x < 0)
		return ((rc->pos.x - floor(rc->u.x)) * rc->t_delta_x);
	else
		return ((floor(rc->u.x) + 1.0f - rc->pos.x) * rc->t_delta_x);
}

float	get_t_max_y(t_raycast *rc)
{
	if (rc->v.y < 0)
		return ((rc->pos.y - floor(rc->u.y)) * rc->t_delta_y);
	else
		return ((floor(rc->u.y) + 1.0f - rc->pos.y) * rc->t_delta_y);
}
