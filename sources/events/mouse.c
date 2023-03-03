/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:30:07 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/03 14:34:42 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	void	mouse_move_right(t_data *data, int diff, int x, int y)
{
	data->mouse.x = x;
	while (diff-- != 0)
		data->player.angle = fix_ang(data->player.angle - 0.5);
	if (x > WINDOW_WIDTH * 0.7)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			(WINDOW_WIDTH / 2), y);
		data->mouse.x = (WINDOW_WIDTH / 2);
	}
}

static	void	mouse_move_left(t_data *data, int diff, int x, int y)
{
	data->mouse.x = x;
	while (diff-- != 0)
		data->player.angle = fix_ang(data->player.angle + 0.5);
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

	diff = fabs(data->mouse.x - x);
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