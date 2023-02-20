/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/20 18:37:46 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// TEMPORARY FUNCTIONS
// static void	image_pixel_put(t_data *data, int width, int height, int color);

static	void	draw_background(t_data *data)
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

static	void	print_wall(t_data *data, int y, int x)
{
	int	end_y;
	int	end_x;
	int	new_x;

	end_y = y + TEXTURE_SIZE;
	end_x = x + TEXTURE_SIZE;
	if (data->win_ptr != NULL)
	{
		while (y < end_y)
		{
			new_x = x;
			while (new_x < end_x)
			{
				image_pixel_put(data, new_x, y, 0x8FDBB5);
				new_x++;
			}
			y++;
		}
	}
}

static	void	draw_wall(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->config->map[y])
	{
		x = 0;
		while (data->config->map[y][x])
		{
			if (data->config->map[y][x] == '1')
				print_wall(data, y * TEXTURE_SIZE, x * TEXTURE_SIZE);
			x++;
		}
		y++;
	}
}

static	void	draw_player(t_data *data)
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

/* static	void	draw_player(t_data *data)
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
} */

// MAIN FUNCTIONS

void	image_pixel_put(t_data *data, int width, int height, int color)
{
	int		i;
	char	*pixel;

	i = data->img.bpp - 8;
	pixel = data->img.addr
		+ (height * data->img.line_len + width * (data->img.bpp / 8));
	while (i >= 0)
	{
		if (data->img.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (data->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}


int	render(t_data *data)
{
	draw_background(data);
	draw_wall(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	else if (keysym == XK_w)
	{
		data->player.y -= (TEXTURE_SIZE / 16);
		if (data->config->map[(int)data->player.y][(int)data->player.x] != '1')
			draw_player(data);
	}
	else if (keysym == XK_a)
	{
		data->player.x -= (TEXTURE_SIZE / 16);
		draw_player(data);
	}
	else if (keysym == XK_s)
	{
		data->player.y += (TEXTURE_SIZE / 16);
		draw_player(data);
	}
	else if (keysym == XK_d)
	{
		data->player.x += (TEXTURE_SIZE / 16);
		draw_player(data);
	}
	
	return (0);
}

/* int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	else if (keysym == XK_w)
	{
		data->player.y += 64;
		draw_player(data, data->player.x, data->player.y);
	}
	else if (keysym == XK_a)
	{
		data->player.x -= 64;
		draw_player_move(data, data->player.x, data->player.y);
	}
	else if (keysym == XK_s)
	{
		data->player.y += 64;
		draw_player_move(data, data->player.x, data->player.y);
	}
	else if (keysym == XK_d)
	{
		data->player.x -= 64;
		draw_player_move(data, data->player.x, data->player.y);
	}
	
	return (0);
} */
