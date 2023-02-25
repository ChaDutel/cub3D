/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/25 15:23:45 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static	void	player_angle(t_data *data, t_config *config, int px, int py)
{
	if (config->map[py][px] == 'N')
		data->player.angle = 180;
	if (config->map[py][px] == 'S')
		data->player.angle = 0;
	if (config->map[py][px] == 'E')
		data->player.angle = 270;
	if (config->map[py][px] == 'W')
		data->player.angle = 90;
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
	while (config->map[py] && !ft_isalpha(config->map[py][px]))
	{
		px = 0;
		while (config->map[py][px] && !ft_isalpha(config->map[py][px]))
			px++;
		if (ft_isalpha(config->map[py][px]))
			break ;
		py++;
	}
	data->player.x = (float)px * TEXTURE_SIZE + (TEXTURE_SIZE / 2);
	data->player.y = (float)py * TEXTURE_SIZE + (TEXTURE_SIZE / 2);
	data->mini_player.x = data->player.x;
	data->mini_player.y = data->player.y;
	player_angle(data, config, px, py);
	data->mini_player.angle = data->player.angle - 90;
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
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data.img.mlx_img)
		return (free_mlx(&data));
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, \
		&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 17, (1L << 2), &close_window, &data);
	mlx_hook(data.win_ptr, 2, (1L << 0), &handle_keypress, &data);
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
		ft_putstr_fd("Error\nError : Only one parameter needed\n", 2);
		return (0);
	}
	if (parsing(argv[1], &config) == -1)
	{
		free_config(&config);
		return (0);
	}
	if (run_mlx(&config) == -1)
		return (error_msg("Error : MLX function failed"));
	free_config(&config);
	return (0);
}
