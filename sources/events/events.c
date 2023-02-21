/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/21 01:28:09 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
	draw_minimap_background(data);
	draw_minimap(data);
	draw_minimap_player(data);
	raycaster(data);
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
		//if (data->config->map[(int)data->player.y][(int)data->player.x] != '1')
		draw_minimap_player(data);
	}
	else if (keysym == XK_a)
	{
		data->player.x -= (TEXTURE_SIZE / 16);
		draw_minimap_player(data);
	}
	else if (keysym == XK_s)
	{
		data->player.y += (TEXTURE_SIZE / 16);
		draw_minimap_player(data);
	}
	else if (keysym == XK_d)
	{
		data->player.x += (TEXTURE_SIZE / 16);
		draw_minimap_player(data);
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
