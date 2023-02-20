/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:35:41 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/20 17:17:38 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_player_move(t_data *data, int px, int py)
{
	float	end_x;
	float	end_y;
	float	x;
	float	y;

	end_x = px + (TEXTURE_SIZE / 16);
	end_y = py + (TEXTURE_SIZE / 16);
	if (data->win_ptr != NULL)
	{
		y = py - (TEXTURE_SIZE / 16);
		while (y < end_y)
		{
			x = px - (TEXTURE_SIZE / 16);
			while (x < end_x)
			{
				image_pixel_put(data, x, y, 0xFFFF00);
				x += 1;
			}
			y += 1;
		}
	}
}