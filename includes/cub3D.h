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

// MACRO

//coordinates
# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define F 4
# define C 5
# define NO_COORD -1

// STRUCTURES

typedef struct s_config
{
	char	**elems;
	char	**map;
} t_config;

//***************//
//    PARSING    //
//***************//

// PARSING
int	parsing(char *config_file, t_config *config);

// PRE PARSING
int	pre_parsing(char *config_file);

// PRE PARSING UTILS
int	find_coordinate(char *line, int *iter);
int	mini_check_coordinate(int *iter);
int	check_nb_coordinate(int *iter);
int	check_map_elems(char *line);

// SPLIT_CONFIG
//int	split_config(char *config_file, t_config *config);

// PARSE ELEM

// PARSE MAP
//int	parse_map(t_config *config);


//***************//
//      EXEC     //
//***************//

//***************//
//      MISC     //
//***************//

// ERROR HANDLING
int	error_msg(char *msg);

// FREE MEMORY

#endif