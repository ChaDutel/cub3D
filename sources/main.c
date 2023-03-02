/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulip <tulip@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/02 18:46:43 by tulip            ###   ########lyon.fr   */
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
	data->mini_player.angle = data->player.angle;
}
static	void	init_textures(t_data *data)
{
	data->tex[NO].mlx_img = NULL;
	data->tex[SO].mlx_img = NULL;
	data->tex[EA].mlx_img = NULL;
	data->tex[WE].mlx_img = NULL;
}

static	int	load_textures(t_data *data)
{
	int	i;
	int	j;

	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img.mlx_img)
		return (-1);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, \
		&data->img.line_len, &data->img.endian);
	j = 0;
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
			&data->tex[j].bpp, &data->tex[j].line_len, &data->tex[j].endian);
		j++;
	}
	return (0);
}

static	void	init_mini_struct(t_data *data, t_config *config)
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
	data->mini_player.x = data->player.x;
	data->mini_player.y = data->player.y;
	player_angle(data, config, px, py);
}

static	int	run_mlx(t_config *config)
{
	t_data		data;

	init_mini_struct(&data, config);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "La promenade des amoureux");
	if (!data.win_ptr)
		return (free_mlx(&data));
	if (load_textures(&data) == -1)
		return (free_mlx(&data));
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 17, (1L << 2), &close_window, &data);
	mlx_hook(data.win_ptr, 2, (1L << 0), &handle_keypress, &data);
	//mlx_mouse_hide(data.mlx_ptr, data.win_ptr);
		// mlx_hook(data.win_ptr, 4, 0x4, event_mouse_press, &data);
		// mlx_hook(data.win_ptr, 5, 0x8, event_mouse_release, &data);
	//mlx_hook(data.win_ptr, 6, 0x40, event_mouse_move, &data);
	mlx_loop(data.mlx_ptr);
	free_mlx(&data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	config;

	config.elems = NULL;
	config.map = NULL;
	if (argc != 2)
	{
		ft_putstr_fd("Error\nOnly one parameter needed\n", 2);
		return (0);
	}
	if (parsing(argv[1], &config) == -1)
	{
		free_config(&config);
		return (0);
	}
	if (run_mlx(&config) == -1)
	{
		free_config(&config);
		return (error_msg("MLX function failed\n"));
	}
	free_config(&config);
	return (0);
}
