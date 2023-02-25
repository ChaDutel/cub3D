/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/02/25 04:36:34 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float FixAng(float a)
{
	if(a > 359.0)
		a -= 360.0;
	if(a < 0.0)
		a += 360.0;
	return (a);
}

float degToRad(float a)
{
	return (a * PI / 180.0);
}

static	void	draw_floor(t_data *data, int x, int start, int stop)
{
	while (start < stop)
	{
		image_pixel_put(data, x, start, 0x00FF00);
		start++;
	}
}

static	void	draw_ceilling(t_data *data, int x, int start, int stop)
{
	while (start < stop)
	{
		image_pixel_put(data, x, start, 0x0000FF);
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

void	raycaster(t_data *data)
{
	t_raymath	rc;

	rc.nb_ray = 0;
	rc.ray.angle = FixAng(data->player.angle + ((float)FOV / 2.0));
	while (rc.nb_ray < WINDOW_WIDTH)
	{
		rc.ray.x = data->player.x / (float)TEXTURE_SIZE;
		rc.ray.y = data->player.y / (float)TEXTURE_SIZE;
		float raycos = -cos(degToRad(rc.ray.angle)) / (float)TEXTURE_SIZE;
		float raysin = -sin(degToRad(rc.ray.angle)) / (float)TEXTURE_SIZE;
		char	wall = '0';
		while (wall != '1')
		{
			rc.ray.x += raycos;
			rc.ray.y += raysin;
			wall = data->config->map[(int)rc.ray.y][(int)rc.ray.x];
		}

		float distance = sqrt(pow(data->player.x / TEXTURE_SIZE - rc.ray.x, 2) + pow(data->player.y / TEXTURE_SIZE - rc.ray.y, 2));
		distance = distance * cos(degToRad(FixAng(rc.ray.angle - data->player.angle)));
		float wallHeight = floor(PLAYER_HEIGHT / distance);

		draw_ceilling(data, rc.nb_ray, 0, PLAYER_HEIGHT - wallHeight);
        draw_floor(data, rc.nb_ray, PLAYER_HEIGHT + wallHeight, WINDOW_HEIGHT);
        draw_wall(data, rc.nb_ray, PLAYER_HEIGHT - wallHeight, PLAYER_HEIGHT + wallHeight);
		
		//rc.ray.x *= (float)TEXTURE_SIZE;
		//rc.ray.y *= (float)TEXTURE_SIZE;
		//bresenham_line(data, &rc);
		rc.ray.angle = FixAng(rc.ray.angle - ANGLE_INCREMENT);
		rc.nb_ray++;
	}
}
