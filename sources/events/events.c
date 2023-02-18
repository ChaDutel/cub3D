/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/18 13:06:42 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

static void	image_pixel_put(t_data *data, int width, int height, int color)
{
	char    *pixel;

    pixel = data->img.addr + (height * data->img.line_len + width * (data->img.bpp / 8));
	*(int *)pixel = color;
}

int render(t_data *data)
{
	int	height;
	int	width;

    if (data->win_ptr != NULL)
	{
		height = 0;
		while(height < WINDOW_HEIGHT)
		{
			width = 0;
			while(width < WINDOW_WIDTH)
			{
				image_pixel_put(data, width, height, 0xFF0000);
				width++;
			}
			height++;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
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
	return (0);
}