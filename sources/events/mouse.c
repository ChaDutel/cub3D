/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:07 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/26 17:06:05 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// int		mouse_manager(int button, int x, int y, void *param)
// {
// 	t_window	*mlx_infos;

// 	mlx_infos = (t_window *)param;
// 	putstr_info_int("Button : ", button, 1);
// 	putstr_info_int("X : ", x, 1);
// 	putstr_info_int("Y : ", y, 1);
// 	return (0);
// }

// int		event_mouse_press(int button, int x, int y, t_data *data)
// {
// 	(void)x;
// 	(void)y;
// 	if (button == 1 && data->health > 0 && data->equiped & INV_GUN &&
// 		data->weaponcd == 0 && data->ammo > 0)
// 	{
// 		data->firing = 1;
// 		data->weaponcd = data->weaponbasecd;
// 		data->ammo--;
// 	}
// 	return (0);
// }

// int		event_mouse_release(int button, int x, int y, t_data *data)
// {
// 	(void)x;
// 	(void)y;
// 	if (button == 1)
// 		data->firing = 0;
// 	return (0);
// }

void	mouse_move_right(t_data *data, int diff, int x, int y)
{
	data->mouse.x = x;
	while (diff-- != 0)
		rotate_right(data, 0.5);
	if (x > WINDOW_WIDTH * 0.7)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			(WINDOW_WIDTH / 2), y);
		data->mouse.x = (WINDOW_WIDTH / 2);
	}
}

void	mouse_move_left(t_data *data, int diff, int x, int y)
{
	data->mouse.x = x;
	while (diff-- != 0)
		rotate_left(data, 0.5);
	if (x < (WINDOW_WIDTH * 0.3))
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			(WINDOW_WIDTH / 2), y);
		data->mouse.x = (WINDOW_WIDTH / 2);
	}
}

int	event_mouse_move(int x, int y, t_data *data)
{
	int	diff;

	diff = abs(data->mouse.x - x);
	if (diff > 6)
		diff = 6;
	if (y < (WINDOW_HEIGHT * 0.3) || y > (WINDOW_HEIGHT * 0.7))
		mlx_mouse_move(data->mlx_ptr, data->win_ptr, x,
			(WINDOW_HEIGHT / 2));
	if (x > data->mouse.x)
		mouse_move_right(data, diff, x, y);
	else if (x < data->mouse.x)
		mouse_move_left(data, diff, x, y);
	return (0);
}
