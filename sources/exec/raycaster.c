/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/02/24 19:25:21 by maxperei         ###   ########lyon.fr   */
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
		//float distance = sqrt(pow(data->player.x - rc.ray.x, 2) + pow(data->player.y - rc.ray.y, 2));
		rc.ray.x *= (float)TEXTURE_SIZE;
		rc.ray.y *= (float)TEXTURE_SIZE;
		bresenham_line(data, &rc);
		rc.ray.angle = FixAng(rc.ray.angle - ANGLE_INCREMENT);
		rc.nb_ray++;
	}
}
