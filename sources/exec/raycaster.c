/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/02/25 17:45:57 by maxperei         ###   ########lyon.fr   */
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

static	void	draw_wall(t_data *data, int x, int start, int stop)
{
	while (start < stop)
	{
		image_pixel_put(data, x, start, 0xFF0000);
		start++;
	}
}

static	void	draw_projection(t_data *data, t_raymath *rc)
{
	float	distance;
	float	wall_height;

	distance = sqrt(pow(data->player.x / TEXTURE_SIZE - rc->ray.x, 2)
			+ pow(data->player.y / TEXTURE_SIZE - rc->ray.y, 2));
	distance = distance * cos(deg_to_rad(fix_ang(rc->ray.angle
					- data->player.angle)));
	wall_height = floor(PLAYER_HEIGHT / distance);
	draw_ceilling(data, rc->nb_ray, 0, PLAYER_HEIGHT - wall_height);
	draw_floor(data, rc->nb_ray, PLAYER_HEIGHT + wall_height, WINDOW_HEIGHT);
	draw_wall(data, rc->nb_ray, PLAYER_HEIGHT - wall_height,
		PLAYER_HEIGHT + wall_height);
}

void	raycaster(t_data *data)
{
	t_raymath	rc;
	float		ray_cos;
	float		ray_sin;
	char		map_elem;

	rc.nb_ray = 0;
	rc.ray.angle = fix_ang(data->player.angle + ((float)FOV / 2.0));
	while (rc.nb_ray < WINDOW_WIDTH)
	{
		rc.ray.x = data->player.x / (float)TEXTURE_SIZE;
		rc.ray.y = data->player.y / (float)TEXTURE_SIZE;
		ray_cos = -cos(deg_to_rad(rc.ray.angle)) / (float)TEXTURE_SIZE;
		ray_sin = -sin(deg_to_rad(rc.ray.angle)) / (float)TEXTURE_SIZE;
		map_elem = '0';
		while (map_elem != '1')
		{
			rc.ray.x += ray_cos;
			rc.ray.y += ray_sin;
			map_elem = data->config->map[(int)rc.ray.y][(int)rc.ray.x];
		}
		draw_projection(data, &rc);
		rc.ray.angle = fix_ang(rc.ray.angle - ANGLE_INCREMENT);
		rc.nb_ray++;
	}
}
