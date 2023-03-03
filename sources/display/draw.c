/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:06:51 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/03 12:22:25 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	image_pixel_put(t_data *data, int width, int height, int color)
{
	char	*pixel;

	if (width < 0 || height < 0 || width >= WINDOW_WIDTH \
		|| height >= WINDOW_HEIGHT)
		return ;
	pixel = data->img.addr
		+ (height * data->img.line_len + width * (data->img.bpp / 8));
	*(int *)pixel = color;
}

void	draw_floor(t_data *data, int x, int start, int stop)
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

void	draw_ceilling(t_data *data, int x, int start, int stop)
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

void	draw_texture(t_data *data, t_raycast *rc, int start, int stop)
{
	int	current;
	int	texture_type;
	int	color;

	current = start;
	texture_type = find_texture_type(rc);
	while (current < stop)
	{
		color = get_texture_color(data, rc, current - start, texture_type);
		image_pixel_put(data, rc->nb_ray, current, color);
		current++;
	}
}

void	draw_image(t_data *data, t_raycast *rc)
{
	if (rc->wall_dist == 0)
		rc->wall_height = WINDOW_HEIGHT / 2;
	else
		rc->wall_height = WINDOW_HEIGHT / 2 / rc->wall_dist;
	draw_floor(data, rc->nb_ray, WINDOW_HEIGHT / 2
		+ rc->wall_height, WINDOW_HEIGHT);
	draw_ceilling(data, rc->nb_ray, 0,
		WINDOW_HEIGHT / 2 - rc->wall_height);
	draw_texture(data, rc, WINDOW_HEIGHT / 2 - rc->wall_height,
		WINDOW_HEIGHT / 2 + rc->wall_height);
}
