/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/20 17:18:22 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// static	void	print_map(t_config *config)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	while (config->map[i])
// 	{
// 		j = 0;
// 		while (config->map[i][j])
// 		{
// 			printf("%c", config->map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

// static	void	print_elems(t_config *config)
// {
// 	int	i;

// 	i = 0;
// 	while (config->elems[i])
// 	{
// 		ft_putstr(config->elems[i++]);
// 		ft_putchar('\n');
// 	}
// }

// static void	test_mlx(void)
// {
// 	void	*img;
// 	// char	*relative_path = "./maps/grass_test.xpm";
// 	// int		img_width;
// 	// int		img_height;
// 	void 	*mlx;
// 	void	*win;
// 	int pixel_bits;
// 	int line_bytes;
// 	int endian;
// 	char *buffer;
	
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 3840, 2160, "La promenade des amoureux"); //fait la fenetre
// 	//img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
// 	img = mlx_new_image(mlx, 3840, 2160);
// 	buffer = mlx_get_data_addr(img, &pixel_bits, &line_bytes, &endian);
// 	buffer[12000] = 255;
// 	int	y = 0, x;
// 	while (y != 2160)
// 	{
// 		x = 0;
// 		while (x != 3840)
// 		{
// 			buffer[y * line_bytes + x * 4 + 2] = 255;
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(mlx, win, img, 0, 0);
// 	mlx_loop(mlx);
// 	(void)win;
// 	(void)img;
// }
static	void	find_player_direction(t_data *data, t_config *config, int px, int py)
{
	if (config->map[py][px] == 'N')
		data->player.dir = PI / 2;
	if (config->map[py][px] == 'S')
		data->player.dir = (3 * PI) / 2;
	if (config->map[py][px] == 'E')
		data->player.dir = 2 * PI;
	if (config->map[py][px] == 'W')
		data->player.dir = PI;
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
	find_player_direction(data, config, px, py);
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
	// print_map(&config);
	// print_elems(&config);
	if (run_mlx(&config) == -1)
		return (error_msg("Error : MLX function failed"));
	free_config(&config);
	return (0);
}
