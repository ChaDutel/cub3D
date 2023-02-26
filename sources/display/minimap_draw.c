/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:46:24 by tulip             #+#    #+#             */
/*   Updated: 2023/02/26 11:58:09 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void draw_map_circle(t_data *data, float xx, float yy, int i)
{
    float	x;
    float	y;
    float	co;
    float	si;
    float	angle = 0;
    int		player_size = TEXTURE_SIZE / 32;

    while (angle < 2 * PI)
    {
        i = 0;
        co = cos(angle);
        si = sin(angle);
        while (i != 150)
        {
            x = i * co + data->mini_player.x;
            y = i * si + data->mini_player.y;
            if ((((int)x / TEXTURE_SIZE) >= 0 && ((int)x / TEXTURE_SIZE) < (int)data->config->x) && (((int)y / TEXTURE_SIZE) >= 0 && ((int)y / TEXTURE_SIZE) < (int)data->config->y)) // check don't go too far, si depasse pas la map
            {
                if (data->config->map[(int)y / TEXTURE_SIZE][(int)x / TEXTURE_SIZE] == '1')
                    image_pixel_put(data, (yy + i * si) + player_size, (xx + i * co) + player_size, 0x8FDBB5);
                else
                    image_pixel_put(data, (yy + i * si) + player_size, (xx + i * co) + player_size, 0xD3D3D3);
            }
            i++;
        }
        angle += 0.3 * PI / 180;
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
