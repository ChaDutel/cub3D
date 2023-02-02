/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:02:27 by cdutel-l          #+#    #+#             */
/*   Updated: 2023/02/02 22:11:37 by charline         ###   ########.fr       */
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
	return (0);
}
