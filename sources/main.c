/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/26 12:57:50 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static	int	load_images(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img.mlx_img)
		return (-1);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, \
		&data->img.line_len, &data->img.endian);
		
	data->tex_no.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, &data->config->elems[NO][3], &data->tex_no.width, &data->tex_no.height);
	if (!data->tex_no.mlx_img)
		return (-1);
	data->tex_no.addr = mlx_get_data_addr(data->tex_no.mlx_img, &data->tex_no.bpp, 
		&data->tex_no.line_len, &data->tex_no.endian);
		
	data->tex_so.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, &data->config->elems[SO][3], &data->tex_so.width, &data->tex_so.height);
	if (!data->tex_so.mlx_img)
		return (-1);
	data->tex_so.addr = mlx_get_data_addr(data->tex_so.mlx_img, &data->tex_so.bpp, 
		&data->tex_so.line_len, &data->tex_so.endian);
		
	data->tex_ea.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, &data->config->elems[EA][3], &data->tex_ea.width, &data->tex_ea.height);
	if (!data->tex_ea.mlx_img)
		return (-1);
	data->tex_ea.addr = mlx_get_data_addr(data->tex_ea.mlx_img, &data->tex_ea.bpp, 
		&data->tex_ea.line_len, &data->tex_ea.endian);
		
	data->tex_we.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, &data->config->elems[WE][3], &data->tex_we.width, &data->tex_we.height);
	if (!data->tex_we.mlx_img)
		return (-1);
	data->tex_we.addr = mlx_get_data_addr(data->tex_we.mlx_img, &data->tex_we.bpp, 
		&data->tex_we.line_len, &data->tex_we.endian);
	return (0);
}

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

static	void	init_textures(t_data *data)
{
	data->tex_no.mlx_img = NULL;
	data->tex_so.mlx_img = NULL;
	data->tex_ea.mlx_img = NULL;
	data->tex_we.mlx_img = NULL;
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
	if (load_images(&data) == -1)
		return (free_mlx(&data));
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
	{
		free_config(&config);
		return (error_msg("Error : MLX function failed\n"));
	}
	free_config(&config);
	return (0);
}
