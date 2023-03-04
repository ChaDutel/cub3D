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
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

//coordinates
# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define F 4
# define C 5
# define NO_COORD -1

//colors
# define FLOOR 0
# define CEIL 1
# define R 0
# define G 1
# define B 2

//game
# define PI 3.1415926535
# define TEXTURE_SIZE 64
# define MAX_DOF 100
# define FOV 60

//miscs
# define MAX_AREA 100000

// STRUCTURES

//point and mouse
typedef struct s_point
{
	float	x;
	float	y;
	float	co;
	float	si;
	float	angle;
}	t_point;

//config file
typedef struct s_config
{
	char	**elems;
	char	**map;
	int		colors[2][3];
	size_t	x;
	size_t	y;
}	t_config;

//image specs
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

// direction vector
typedef struct s_dir
{
	float	x;
	float	y;
}	t_dir;

//raycaster values
typedef struct s_raycast
{
	t_dir	u;
	t_dir	v;
	t_point	pos;
	t_point	elem;
	int		side;
	float	step_x;
	float	step_y;
	float	t_max_x;
	float	t_max_y;
	float	t_delta_x;
	float	t_delta_y;
	int		nb_ray;
	float	wall_dist;
	float	ray_angle;
	float	angle_step;
	float	wall_percent;
	float	wall_height;
}	t_raycast;

//mlx struct
typedef struct s_data
{
	t_config	*config;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_img		tex[4];
	t_point		mouse;
	t_point		player;
}	t_data;

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
//     INIT      //
//***************//

void	init_mini_struct(t_data *data, t_config *config);
int		load_textures(t_data *data);

//***************//
//    EVENTS     //
//***************//

// EVENTS
int		render(t_data*data);
int		close_window(t_data *data);
int		handle_keypress(int keysym, t_data *data);

// MOVEMENT
void	dir_up(t_data *data);
void	dir_left(t_data *data);
void	dir_right(t_data *data);
void	dir_down(t_data *data);

//***************//
//    DISPLAY    //
//***************//

// DRAW
void	image_pixel_put(t_data *data, int width, int height, int color);
void	draw_floor(t_data *data, int x, int start, int stop);
void	draw_ceilling(t_data *data, int x, int start, int stop);
void	draw_texture(t_data *data, t_raycast *rc, int start, int stop);
void	draw_image(t_data *data, t_raycast *rc);

// MINIMAP_DRAW
void	draw_minimap_player(t_data *data);

//***************//
//      EXEC     //
//***************//

// RAYCASTER
void	raycaster(t_data *data);
int		find_texture_type(t_raycast *rc);
int		get_texture_color(t_data *data, t_raycast *rc, int height,	\
			int texture_type);

// RAYCEASTER_UTILS
float	get_t_max_x(t_raycast *rc);
float	get_t_max_y(t_raycast *rc);
void	choose_dist(t_data *data, t_raycast *rc);

//***************//
//     MISCS     //
//***************//

// ERROR HANDLING
int		error_msg(char *msg);

// FREE MEMORY
void	free_config(t_config *config);
int		free_mlx(t_data *data);

// LIBC_FT
float	deg_to_rad(float a);
float	fix_ang(float a);
char	*char_join(char *str, char c);

#endif
