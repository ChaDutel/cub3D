/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:36:10 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/03 10:45:49 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static	void	player_angle(t_data *data, t_config *config, int px, int py)
{
	if (config->map[py][px] == 'N')
		data->player.angle = 90;
	if (config->map[py][px] == 'S')
		data->player.angle = 270;
	if (config->map[py][px] == 'E')
		data->player.angle = 0;
	if (config->map[py][px] == 'W')
		data->player.angle = 180;
}

static	void	init_textures(t_data *data)
{
	data->tex[NO].mlx_img = NULL;
	data->tex[SO].mlx_img = NULL;
	data->tex[EA].mlx_img = NULL;
	data->tex[WE].mlx_img = NULL;
}

int	load_textures(t_data *data)
{
	int			i;
	static int	j = 0;

	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img.mlx_img)
		return (-1);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, \
		&data->img.line_len, &data->img.endian);
	while (j < 4)
	{
		i = 2;
		while (data->config->elems[j][i] && data->config->elems[j][i] == ' ')
			i++;
		data->tex[j].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
				&data->config->elems[j][i], &data->tex[j].width,
				&data->tex[j].height);
		if (!data->tex[j].mlx_img)
			return (-1);
		data->tex[j].addr = mlx_get_data_addr(data->tex[j].mlx_img,
				&data->tex[j].bpp, &data->tex[j].line_len,
				&data->tex[j].endian);
		j++;
	}
	return (0);
}

void	init_mini_struct(t_data *data, t_config *config)
{
	int	px;
	int	py;

	px = 0;
	py = 0;
	data->config = config;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img.mlx_img = NULL;
	init_textures(data);
	while (config->map[py] && !ft_isalpha(config->map[py][px]))
	{
		px = 0;
		while (config->map[py][px] && !ft_isalpha(config->map[py][px]))
			px++;
		if (ft_isalpha(config->map[py][px]))
			break ;
		py++;
	}
	data->player.x = px + 0.5f;
	data->player.y = py + 0.5f;
	player_angle(data, config, px, py);
}
