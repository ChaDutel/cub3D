/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 05:15:50 by tulip             #+#    #+#             */
/*   Updated: 2023/02/22 07:56:55 by tulip            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	void	small_slope_draw(t_point current, t_point ray, t_point delta
	, t_data *data)
{
	int	i;
	int	pk;

	i = 0;
	pk = 2 * delta.y - delta.x;
	while (i < delta.x)
	{
		if (current.x < ray.x)
			current.x++;
		else
			current.x--;
		if (pk < 0)
		{
			image_pixel_put(data, current.x, current.y, 0x0000FF);
			pk = pk + 2 * delta.y;
		}
		else
		{
			if (current.y < ray.y)
				current.y++;
			else
				current.y--;
			image_pixel_put(data, current.x, current.y, 0x0000FF);
			pk = pk + 2 * delta.y - 2 * delta.x;
		}
		i++;
	}
}

static	void	big_slope_draw(t_point current, t_point ray, t_point delta
	, t_data *data)
{
	int	i;
	int	pk;

	i = 0;
	pk = 2 * delta.x - delta.y;
	while (i < delta.y)
	{
		if (current.y < ray.y)
			current.y++;
		else
			current.y--;
		if (pk < 0)
		{
			image_pixel_put(data, current.x, current.y, 0xFF0000);
			pk = pk + 2 * delta.x;
		}
		else
		{
			if (current.x < ray.x)
				current.x++;
			else
				current.x--;
			image_pixel_put(data, current.x, current.y, 0xFF0000);
			pk = pk + 2 * delta.x - 2 * delta.y;
		}
		i++;
	}
}

void	bresenham_line(t_data *data, t_raymath *rc)
{
	t_point	delta;
	t_point	current;
	t_point ray;
	
	delta.x = abs((int)roundf(rc->ray.x - data->player.x));
	delta.y = abs((int)roundf(rc->ray.y - data->player.y));
	current.x = (int)data->player.x;
	current.y = (int)data->player.y;
	ray.x = (int)rc->ray.x;
	ray.y = (int)rc->ray.y;
	if (delta.x > delta.y)
		small_slope_draw(current, ray, delta, data);
	else
		big_slope_draw(current, ray, delta, data);
}
