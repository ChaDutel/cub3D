/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/12 16:05:04 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

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
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, 
					width, height, 0xFF0000);
				width++;
			}
			height++;
		}
	}
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