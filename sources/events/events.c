/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/25 12:51:45 by cdutel-l         ###   ########lyon.fr   */
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

int	render(t_data *data)
{
	//draw_minimap_background(data);
	raycaster(data);
	draw_minimap(data);
	draw_minimap_player(data);
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
		new_direction_up(data);
	else if (keysym == XK_a)
		new_direction_left(data);
	else if (keysym == XK_s)
		new_direction_down(data);
	else if (keysym == XK_d)
		new_direction_right(data);
	else if (keysym == XK_Left)
	{
		data->player.angle += 4;
		data->player.angle = FixAng(data->player.angle);
	}
	else if (keysym == XK_Right)
	{
		data->player.angle -= 4;
		data->player.angle = FixAng(data->player.angle);
	}
	draw_minimap_player(data);
	return (0);
}
