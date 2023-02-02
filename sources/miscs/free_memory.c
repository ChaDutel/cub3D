/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:05 by charline          #+#    #+#             */
/*   Updated: 2023/02/02 20:26:14 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	if (config->elems)
	{
		while (config->elems[i])
		{
			free(config->elems[i]);
			i++;
		}
		free(config->elems);
	}
	i = 0;
	if (config->map)
	{
		while (config->map[i])
		{
			free(config->map[i]);
			i++;
		}
		free(config->map);
	}
	config->elems = NULL;
	config->map = NULL;
}