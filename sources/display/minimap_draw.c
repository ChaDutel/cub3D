/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:46:24 by tulip             #+#    #+#             */
/*   Updated: 2023/02/23 13:48:10 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	void	print_color(t_data *data, int y, int x, int color)
{
	int	end_y;
	int	end_x;
	int	new_x;

	end_y = y + TEXTURE_SIZE - 1;
	end_x = x + TEXTURE_SIZE - 1;
	if (data->win_ptr != NULL)
	{
		while (y < end_y)
		{
			new_x = x;
			while (new_x < end_x)
			{
				image_pixel_put(data, new_x, y, color);
				new_x++;
			}
			y++;
		}
	}
}

void	draw_minimap_background(t_data *data)
{
	int	height;
	int	width;

	if (data->win_ptr != NULL)
	{
		height = 0;
		while (height < WINDOW_HEIGHT)
		{
			width = 0;
			while (width < WINDOW_WIDTH)
			{
				image_pixel_put(data, width, height, 0x888888);
				width++;
			}
			height++;
		}
	}
}

void	draw_minimap(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->config->map[y] && y * TEXTURE_SIZE < WINDOW_HEIGHT)
	{
		x = 0;
		while (data->config->map[y][x] && x * TEXTURE_SIZE < WINDOW_WIDTH)
		{
			if (data->config->map[y][x] == '1')
				print_color(data, y * TEXTURE_SIZE, x * TEXTURE_SIZE, 0x8FDBB5);
			else
				print_color(data, y * TEXTURE_SIZE, x * TEXTURE_SIZE, 0xD3D3D3);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_data *data)
{
	float	end_x;
	float	end_y;
	float	x;
	float	y;

	end_x = data->player.x + (TEXTURE_SIZE / 16);
	end_y = data->player.y + (TEXTURE_SIZE / 16);
	if (data->win_ptr != NULL)
	{
		y = data->player.y - (TEXTURE_SIZE / 16);
		while (y < end_y)
		{
			x = data->player.x - (TEXTURE_SIZE / 16);
			while (x < end_x)
			{
				image_pixel_put(data, x, y, 0xFFFF00);
				x += 1;
			}
			y += 1;
		}
	}
////////////////////////////////////////////////////////////////
	t_raymath	rc;
	rc.ray.x = data->player.x + 10;
	rc.ray.y = data->player.y + 10;
	image_pixel_put(data, rc.ray.x, rc.ray.y, 0xFFFF00);
	image_pixel_put(data, rc.ray.x + 1, rc.ray.y + 1, 0xFFFF00);
	image_pixel_put(data, rc.ray.x + 2, rc.ray.y + 2, 0xFFFF00);
	image_pixel_put(data, rc.ray.x + 3, rc.ray.y + 3, 0xFFFF00);
	image_pixel_put(data, rc.ray.x + 4, rc.ray.y + 4, 0xFFFF00);
	image_pixel_put(data, rc.ray.x + 5, rc.ray.y + 5, 0xFFFF00);
}
