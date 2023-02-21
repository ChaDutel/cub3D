/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:46:24 by tulip             #+#    #+#             */
/*   Updated: 2023/02/21 02:37:28 by tulip            ###   ########lyon.fr   */
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
}

void	draw_ray(t_data *data, t_raymath *rc)
{
	t_point	delta;
	t_point	current;
	int		pk;
	int		i;

	delta.x = (int)roundf(rc->ray.x - data->player.x);
	delta.y = (int)roundf(rc->ray.y - data->player.y);
	current.x = (int)data->player.x;
	current.y = (int)data->player.y;
	i = 0;
	if (abs(delta.x) > abs(delta.y))
	{
		pk = (2 * abs(delta.y)) - abs(delta.x);
		while (i < abs(delta.x))
		{
			current.x++;
			if (pk < 0)
				pk += (2 * abs(delta.y));
			else
			{
				current.y++;
				pk += (2 * abs(delta.y)) - (2 * abs(delta.x));
			}
			image_pixel_put(data, current.x, current.y, 0x0000FF);
			i++;
		}
	}
	else
	{
		pk = (2 * abs(delta.x)) - abs(delta.y);
		while (i < abs(delta.y))
		{
			current.y++;
			if (pk < 0)
				pk += (2 * abs(delta.x));
			else
			{
				current.x++;
				pk += (2 * abs(delta.x)) - (2 * abs(delta.y));
			}
			image_pixel_put(data, current.x, current.y, 0x0000FF);
			i++;
		}
	}	
}
