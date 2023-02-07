/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/07 18:33:01 by cdutel-l         ###   ########lyon.fr   */
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

static void	test_mlx(void)
{
	void	*img;
	// char	*relative_path = "./maps/grass_test.xpm";
	// int		img_width;
	// int		img_height;
	void 	*mlx;
	void	*win;
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, 3840, 2160, "La promenade des amoureux"); //fait la fenetre
	//img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	img = mlx_new_image(mlx, 3840, 2160);
	buffer = mlx_get_data_addr(img, &pixel_bits, &line_bytes, &endian);
	buffer[12000] = 255;
	int	y = 0, x;
	while (y != 2160)
	{
		x = 0;
		while (x != 3840)
		{
			buffer[y * line_bytes + x * 4 + 2] = 255;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	(void)win;
	(void)img;
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
	test_mlx();
	free_config(&config);
	return (0);
}
