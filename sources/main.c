/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/07 17:01:23 by cdutel-l         ###   ########lyon.fr   */
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
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 3840, 2160, "La promenade des amoureux");
	mlx_loop(mlx);
	(void)win;
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
