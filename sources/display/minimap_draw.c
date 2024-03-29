/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:46:24 by tulip             #+#    #+#             */
/*   Updated: 2023/03/03 14:53:06 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	draw_map_circle_norm(t_data *data, float xx, float yy, float *i)
{
	int		player_size;
	float	x;
	float	y;

	player_size = TEXTURE_SIZE / 32;
	x = *i * data->player.co + (data->player.x * TEXTURE_SIZE);
	y = *i * data->player.si + (data->player.y * TEXTURE_SIZE);
	x /= TEXTURE_SIZE;
	y /= TEXTURE_SIZE;
	if ((((int)x) >= 0 && ((int)x) < (int)data->config->x) \
		&& (((int)y) >= 0 && ((int)y) < (int)data->config->y))
	{
		if (data->config->map[(int)y][(int)x] == '1'
			|| data->config->map[(int)y][(int)x] == ' ')
			image_pixel_put(data, (yy + *i * data->player.co) \
			+ player_size, (xx + *i * data->player.si) \
			+ player_size, 0x8FDBB5);
		else
			image_pixel_put(data, (yy + *i * data->player.co) \
			+ player_size, (xx + *i * data->player.si) \
			+ player_size, 0xD3D3D3);
	}
	*i += 1;
}

static void	draw_map_circle(t_data *data, float xx, float yy, float i)
{
	float	angle;

	angle = 0;
	while (angle < 2 * PI)
	{
		i = 0;
		data->player.co = cos(angle);
		data->player.si = sin(angle);
		while (i != 150)
			draw_map_circle_norm(data, xx, yy, &i);
		angle += 0.3 * PI / 180;
	}
}

void	draw_minimap_player(t_data *data)
{
	float	end_x;
	float	end_y;
	float	x;
	float	y;

	end_x = 150 + (TEXTURE_SIZE / 16);
	end_y = 150 + (TEXTURE_SIZE / 16);
	draw_map_circle(data, 150, 150, 0);
	if (data->win_ptr != NULL)
	{
		y = 150 - (TEXTURE_SIZE / 16);
		while (y < end_y)
		{
			x = 150 - (TEXTURE_SIZE / 16);
			while (x < end_x)
			{
				image_pixel_put(data, x, y, 0xF485FF00);
				x += 1;
			}
			y += 1;
		}
	}
}
