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
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "../libft/includes/libft.h"
# include "../mlx_linux/mlx.h"

// MACRO

//window
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 512

//coordinates
# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define F 4
# define C 5
# define NO_COORD -1

//game
# define PI 3.1415926535
# define TEXTURE_SIZE 64
# define MAX_DOF 100
# define FOV 60
# define PLAYER_HEIGHT (TEXTURE_SIZE / 2)

//miscs
# define MAX_AREA 100000

// STRUCTURES

typedef	struct s_point
{
	int	x;
	int	y;
} t_point;

//config file
typedef struct s_config
{
	char	**elems;
	char	**map;
	int		colors[2][3];
	size_t	x;
	size_t	y;
} t_config;

//image specs
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

//vector
typedef	struct s_vector
{
	float	x;
	float	y;
	float	angle;
	float	new_x;
	float	new_y;
} t_vector;

//raycaster values
typedef	struct s_raymath
{
	t_vector	ray;
	int			nb_ray;
	int			dof_counter;
	float		aTan;
	float		y_off;
	float		x_off;
	int			elem_x;
	int			elem_y;
	int			elem_pos;
} t_raymath;

//mlx struct
typedef struct s_data
{
	t_config	*config;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_vector	player;
} t_data;



//***************//
//    PARSING    //
//***************//

// PARSING
int		parsing(char *config_file, t_config *config);

// PRE PARSING
int		pre_parsing(char *config_file);

// PRE PARSING UTILS
int		find_coordinate(char *line, int *iter);
int		mini_check_coordinate(int *iter);
int		check_nb_coordinate(int *iter);
int		check_map_elems(char *line);

// SPLIT_CONFIG
int		split_config(char *config_file, t_config *config);

// SPLIT_CONFIG_UTILS
int		add_coordinate(char *line, int *elem_index, t_config *config);
int		prepare_map(int fd, t_config *config);
void	trim_elems(t_config *config);
void	sort_elems(t_config *config);

// PARSE ELEM
int		parse_elems(t_config *config);

// PARSE COLORS
int		check_colors_values(t_config *config, int i, int j);

// PARSE MAP
int		parse_map(t_config *config);

//***************//
//    EVENTS     //
//***************//

// EVENTS
int		render(t_data*data);
int		close_window(t_data *data);
int		handle_keypress(int keysym, t_data *data);
void	image_pixel_put(t_data *data, int width, int height, int color);
void	draw_player_move(t_data *data, int px, int py);
float 	deg_to_rad(int angle);

//***************//
//    DISPLAY    //
//***************//

// MINIMAP_DRAW
void	draw_minimap_background(t_data *data);
void	draw_minimap(t_data *data);
void	draw_minimap_player(t_data *data);

// BRSENHAM_LINE
void	bresenham_line(t_data *data, t_raymath * rc);

//***************//
//      EXEC     //
//***************//

// RAYCAST
void	raycaster(t_data *data);

//***************//
//     MISCS     //
//***************//

// ERROR HANDLING
int		error_msg(char *msg);

// FREE MEMORY
void	free_config(t_config *config);
int		free_mlx(t_data *data);

// LIBC_FT
int 	roundint(int value);
char    *char_join(char *str, char c);

#endif
