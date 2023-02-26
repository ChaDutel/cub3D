/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:29:37 by tulip             #+#    #+#             */
/*   Updated: 2023/02/26 20:11:38 by tulip            ###   ########lyon.fr   */
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

static	int		get_texture_color(t_data *data, int width, int height, float div, float div2)
{
	char	*pixel;
	int		color;
	
	// protect for unusual texture sizes
	pixel = data->tex_no.addr
		+ ((int)(height * div)) * data->tex_no.line_len + ((int)((width * div2)) % 64) * (data->tex_no.bpp / 8);
	color = *(int*)pixel;
	return (color);
}

static	void	draw_wall(t_data *data, int x, int start, int stop)
{
	int	tex_color;
	int	wall_height = stop - start;
	float	div = (float)TEXTURE_SIZE / (wall_height);
	float	div2 = (float)TEXTURE_SIZE / (TEXTURE_SIZE * data->config->x); 
	int	begin = start;
	
	while (start < stop)
	{
		tex_color = get_texture_color(data, x, start - begin, div, div2);
		image_pixel_put(data, x, start, tex_color);
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
	wall_height = floor(rc->player_height / distance);
	draw_ceilling(data, rc->nb_ray, 0, rc->player_height - wall_height);
	draw_floor(data, rc->nb_ray, rc->player_height + wall_height, WINDOW_HEIGHT);
	draw_wall(data, rc->nb_ray, rc->player_height - wall_height,
		rc->player_height + wall_height);
}

void	raycaster(t_data *data)
{
	t_raymath	rc;
	float		ray_cos;
	float		ray_sin;
	char		map_elem;

	rc.nb_ray = 0;
	rc.player_height = WINDOW_HEIGHT / 2;
	rc.ray.angle = fix_ang(data->player.angle + ((float)FOV / 2.0));
	rc.angle_increment = (float)FOV / (float)WINDOW_WIDTH;
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
		rc.ray.angle = fix_ang(rc.ray.angle - rc.angle_increment);
		rc.nb_ray++;
	}
}
