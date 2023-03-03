/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/03/03 12:37:38 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
		data->player.angle = fix_ang(data->player.angle + 4);
	else if (keysym == XK_Right)
		data->player.angle = fix_ang(data->player.angle - 4);
	return (0);
}
