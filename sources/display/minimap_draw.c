/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:46:24 by tulip             #+#    #+#             */
/*   Updated: 2023/02/26 10:35:39 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void draw_map_circle(t_data *data, float xx, float yy, int i)
{
    float    x;
    float    y;
    float    nx;
    float    ny;
    float    co;
    float    si;
    int length = 150;
    float angle = 0;
    // float angle_stepsize = 0.6 PI / 180; //0.1;
    int    texture_si;

    // go through all angles from 0 to 2 * PI radians
    // x = data->player.x;
    // y = data->player.y;
    texture_si = TEXTURE_SIZE / 32;
    while (angle < 2 * PI)
    {
        i = 0;
        // calculate x, y from a vector with known length and angle
        co = cos(angle);
        si = sin(angle);
        while (i != length)
        {
            x = i * co + data->mini_player.x;
            y = i * si + data->mini_player.y;
            nx = i * co + xx;
            ny = i * si + yy;
            // x = i * cos(angle) + data->mini_player.x;
            // y = i * sin(angle) + data->mini_player.y;
            // nx = i * cos(angle) + xx;
            // ny = i * sin(angle) + yy;
            // if () // check don't go too far, si depasse pas la map
            // {
                if (data->config->map[(int)y / TEXTURE_SIZE][(int)x / TEXTURE_SIZE] == '1')
                    image_pixel_put(data, ny + texture_si, nx + texture_si, 0x8FDBB5);
                else
                    image_pixel_put(data, ny + texture_si, nx + texture_si, 0xD3D3D3);
                // if (data->config->map[(int)y / TEXTURE_SIZE][(int)x / TEXTURE_SIZE] == '1')
                //     image_pixel_put(data, ny + (TEXTURE_SIZE / 32), nx + (TEXTURE_SIZE / 32), 0x8FDBB5);
                // else
                //     image_pixel_put(data, ny + (TEXTURE_SIZE / 32), nx + (TEXTURE_SIZE / 32), 0xD3D3D3);
            // }
            //image_pixel_put(data, x + (TEXTURE_SIZE / 16), y + (TEXTURE_SIZE / 16), 0xF485FF00);
            i++;
        }
        angle += 0.6 * PI / 180;
    }
}

void    draw_minimap_player(t_data *data)
{
    float    end_x;
    float    end_y;
    float    x;
    float    y;

    end_x = 150 + (TEXTURE_SIZE / 16);
    end_y = 150 + (TEXTURE_SIZE / 16);
    draw_map_circle(data, end_x - (TEXTURE_SIZE / 16), end_y - (TEXTURE_SIZE / 16), 0);
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

// static	void	print_color(t_data *data, int y, int x, int color)
// {
// 	int	end_y;
// 	int	end_x;
// 	int	new_x;

// 	end_y = y + TEXTURE_SIZE - 1;
// 	end_x = x + TEXTURE_SIZE - 1;
// 	if (data->win_ptr != NULL)
// 	{
// 		while (y < end_y)
// 		{
// 			new_x = x;
// 			while (new_x < end_x)
// 			{
// 				image_pixel_put(data, new_x, y, color);
// 				new_x++;
// 			}
// 			y++;
// 		}
// 	}
// }

// void	draw_minimap_background(t_data *data)
// {
// 	int	height;
// 	int	width;

// 	if (data->win_ptr != NULL)
// 	{
// 		height = 0;
// 		while (height < WINDOW_HEIGHT)
// 		{
// 			width = 0;
// 			while (width < WINDOW_WIDTH)
// 			{
// 				image_pixel_put(data, width, height, 0x888888);
// 				width++;
// 			}
// 			height++;
// 		}
// 	}
// }

// void	draw_minimap(t_data *data)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (data->config->map[y] && y * TEXTURE_SIZE < WINDOW_HEIGHT)
// 	{
// 		x = 0;
// 		while (data->config->map[y][x] && x * TEXTURE_SIZE < WINDOW_WIDTH)
// 		{
// 			if (data->config->map[y][x] == '1')
// 				print_color(data, y * TEXTURE_SIZE, x * TEXTURE_SIZE, 0x8FDBB5);
// 			else
// 				print_color(data, y * TEXTURE_SIZE, x * TEXTURE_SIZE, 0xD3D3D3);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_minimap_player(t_data *data)
// {
// 	float	end_x;
// 	float	end_y;
// 	float	x;
// 	float	y;

// 	end_x = data->mini_player.x + (TEXTURE_SIZE / 16);
// 	end_y = data->mini_player.y + (TEXTURE_SIZE / 16);
// 	if (data->win_ptr != NULL)
// 	{
// 		y = data->mini_player.y - (TEXTURE_SIZE / 16);
// 		while (y < end_y)
// 		{
// 			x = data->mini_player.x - (TEXTURE_SIZE / 16);
// 			while (x < end_x)
// 			{
// 				image_pixel_put(data, x, y, 0xFFFF00);
// 				x += 1;
// 			}
// 			y += 1;
// 		}
// 	}
// }
