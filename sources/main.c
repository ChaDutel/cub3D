/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/03/04 12:01:42 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	mlx_hook(data.win_ptr, 17, 2, &close_window, &data);
	mlx_hook(data.win_ptr, 2, 1, &handle_keypress, &data);
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
