/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:03:42 by maxperei          #+#    #+#             */
/*   Updated: 2023/01/24 15:15:2 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

# include "../libft/includes/libft.h"

typedef struct s_config
{
	char	**elems;
	char	**map;
} t_config;

//***************//
//    PARSING    //
//***************//

int	parsing(char *config_file, t_config *config);
int	parse_elems(char *config_file);
int	split_config(char *config_file, t_config *config);
int	parse_map(t_config *config);

//***************//
//      EXEC     //
//***************//

//***************//
//      MISC     //
//***************//

// ERROR HANDLING
//int	normal_error(char *str);
//int	fatal_error(char *str);

#endif