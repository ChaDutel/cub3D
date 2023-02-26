/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/26 14:31:40 by maxperei         ###   ########lyon.fr   */
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
	raycaster(data);
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
		dir_up(data);
	else if (keysym == XK_a)
		dir_left(data);
	else if (keysym == XK_s)
		dir_down(data);
	else if (keysym == XK_d)
		dir_right(data);
	else if (keysym == XK_Left)
	{
		data->player.angle += 4;
		data->player.angle = fix_ang(data->player.angle);
		data->mini_player.angle -= 4;
		data->mini_player.angle = fix_ang(data->mini_player.angle);
	}
	else if (keysym == XK_Right)
	{
		data->player.angle -= 4;
		data->player.angle = fix_ang(data->player.angle);
		data->mini_player.angle += 4;
		data->mini_player.angle = fix_ang(data->mini_player.angle);
	}
	draw_minimap_player(data);
	return (0);
}
