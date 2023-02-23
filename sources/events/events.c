/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:48:43 by maxperei          #+#    #+#             */
/*   Updated: 2023/02/23 16:54:10 by cdutel-l         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	image_pixel_put(t_data *data, int width, int height, int color)
{
	// int		i;
	char	*pixel;

	if (width < 0 || height < 0 || width >= WINDOW_WIDTH || height >= WINDOW_HEIGHT)
		return ;
	// i = data->img.bpp - 8;
	pixel = data->img.addr
		+ (height * data->img.line_len + width * (data->img.bpp / 8));
	*(int *)pixel = color;
	// while (i >= 0)
	// {
		// if (data->img.endian != 0)
			// *pixel++ = (color >> i) & 0xFF;
		// else
			// *pixel++ = (color >> (data->img.bpp - 8 - i)) & 0xFF;
		// i -= 8;
	// }
}

/* void draw_big_circle(t_data *data)
{
    int x;
	int	y;
    int length = 50;
    float angle = 0.0;
    float angle_stepsize = 0.1;

    // go through all angles from 0 to 2 * PI radians
    while (angle < 2 * PI)
    {
        // calculate x, y from a vector with known length and angle
        x = length * cos(angle);
        y = length * sin(angle);

        // putpixel (screen, x + SCREEN_W / 2, y + SCREEN_H / 2, makecol (255, 255, 255));
        image_pixel_put(data, x + WINDOW_WIDTH / 2, y + WINDOW_HEIGHT / 2, 0xFFFF00);
        angle += angle_stepsize;
    }
} */

void draw_big_circle(t_data *data)
{
    int x;
	int	y;
    int length = 50;
    float angle = 0.0;
    float angle_stepsize = 0.1;

    // go through all angles from 0 to 2 * PI radians
	x = data->player.x;
	y = data->player.y;
    while (angle < 2 * PI)
    {
        // calculate x, y from a vector with known length and angle
        x = length * cos(angle) + data->player.x;
        y = length * sin(angle) + data->player.y;

        // putpixel (screen, x + SCREEN_W / 2, y + SCREEN_H / 2, makecol (255, 255, 255));
        // image_pixel_put(data, x + WINDOW_WIDTH / 2, y + WINDOW_HEIGHT / 2, 0xFFFF00);
        image_pixel_put(data, x + (TEXTURE_SIZE / 16), y + (TEXTURE_SIZE / 16), 0xFFFF00);
        angle += angle_stepsize;
    }
}

void draw_fov_circle(t_data *data)
{
    int x;
	int	y;
    int length = 60;
    float angle = data->player.angle;
    float angle_stepsize = 0.1;

    // go through all angles from 0 to 2 * PI radians
	x = data->player.x;
	y = data->player.y;
    while (angle < 2 * PI)
    {
        // calculate x, y from a vector with known length and angle
        x = length * cos(angle) + data->player.x;
        y = length * sin(angle) + data->player.y;

        // putpixel (screen, x + SCREEN_W / 2, y + SCREEN_H / 2, makecol (255, 255, 255));
        // image_pixel_put(data, x + WINDOW_WIDTH / 2, y + WINDOW_HEIGHT / 2, 0xFFFF00);
        image_pixel_put(data, x + (TEXTURE_SIZE / 16), y + (TEXTURE_SIZE / 16), 0xF0F000);
        angle += angle_stepsize;
    }
}

/* void draw_circle(t_data *data)
{
    int x;
	int	y;
    int length = 50;
    float angle = data->player.angle;
    // float angle = 0.0;
    float angle_stepsize = 0.1;

    // go through all angles from 0 to 2 * PI radians
    while (angle < PI / 3)
    {
        // calculate x, y from a vector with known length and angle
        x = length * cos(angle);
        y = length * sin(angle);

        image_pixel_put(data, x - (TEXTURE_SIZE / 16), y - (TEXTURE_SIZE / 16), 0xFFFF00);
        // putpixel (screen, x + SCREEN_W / 2, y + SCREEN_H / 2, makecol (255, 255, 255));
        angle += angle_stepsize;
    }
} */

int	render(t_data *data)
{
	draw_minimap_background(data);
	draw_minimap(data);
	raycaster(data);
	draw_minimap_player(data);
	draw_fov_circle(data);
	draw_big_circle(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

float deg_to_rad(int angle)
{
	return (angle * PI / 180);
}

float FixAng(float angle)
{
	if(angle >= 2 * PI)
		angle -= 2 * PI;
	if(angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	new_direction_right(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = sin(data->player.angle) * 10.0f + data->player.x;
	new_y = cos(data->player.angle) * 10.0f + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_left(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = -sin(data->player.angle) * 10.0f + data->player.x;
	new_y = -cos(data->player.angle) * 10.0f + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_down(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = cos(data->player.angle) * 10.0f + data->player.x;
	new_y = sin(data->player.angle) * 10.0f + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_up(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = -cos(data->player.angle) * 10.0f + data->player.x;
	new_y = -sin(data->player.angle) * 10.0f + data->player.y;
	// Collision test if(data->config->map[Math.floor(new_y)][Math.floor(new_x)] == 0)
    if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

/* void	new_direction_rotation(t_data *data)
{
	float	new_x;
	float	new_y;
	// new position x = data->player.x(cos(data->player.angle)) - data->player.y(sin(data->player.angle));
	// new position y = data->player.x(sin(data->player.angle)) + data->player.y(cos(data->player.angle));
	new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	
	new_x = cos(data->player.angle) * 10.0f + data->player.x;
	new_y = sin(data->player.angle) * 10.0f + data->player.y;
	
	
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
	//new_vector = (new_x, new_y);
	// new_vector = (x * cos (angle) - y * sin(angle), x * sine (angle) + y * cos(angle));
} */

int rotation_key(int keysym, t_data *data)
{
    if (keysym == XK_Left)
    {
        data->player.angle -= 4 * PI / 180; //10.0f;
		data->player.angle = FixAng(data->player.angle);
		//new_direction_rotation(data);
        draw_minimap_player(data);
    }
    else if (keysym == XK_Right)
	{
		data->player.angle += 4 * PI / 180; //10.0f;
		data->player.angle = FixAng(data->player.angle);
		//new_direction_rotation(data);
        draw_minimap_player(data);
	}
    return (0);
}

/* float FixAng(float angle)
{
	if(angle >= 2 * PI)
		angle -= 2 * PI;
	if(angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	new_direction_right(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = -sin(data->player.angle) * 10.0f + data->player.x;
	new_y = -cos(data->player.angle) * 10.0f + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_left(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = sin(data->player.angle) * 10.0f + data->player.x;
	new_y = cos(data->player.angle) * 10.0f + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_down(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = -cos(data->player.angle) * 10.0f + data->player.x;
	new_y = -sin(data->player.angle) * 10.0f + data->player.y;
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_up(t_data *data)
{
	float	new_x;
	float	new_y;

	// new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	// new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	new_x = cos(data->player.angle) * 10.0f + data->player.x;
	new_y = sin(data->player.angle) * 10.0f + data->player.y;
	// Collision test if(data->config->map[Math.floor(new_y)][Math.floor(new_x)] == 0)
    if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	new_direction_rotation(t_data *data)
{
	float	new_x;
	float	new_y;
	// new position x = data->player.x(cos(data->player.angle)) - data->player.y(sin(data->player.angle));
	// new position y = data->player.x(sin(data->player.angle)) + data->player.y(cos(data->player.angle));
	new_x = data->player.x * cos(data->player.angle) - data->player.y * sin(data->player.angle);
	new_y = data->player.x * sin(data->player.angle) + data->player.y * cos(data->player.angle);
	
	new_x = cos(data->player.angle) * 10.0f + data->player.x;
	new_y = sin(data->player.angle) * 10.0f + data->player.y;
	
	
	if(data->config->map[(int)new_y / TEXTURE_SIZE][(int)new_x / TEXTURE_SIZE] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
	//new_vector = (new_x, new_y);
	// new_vector = (x * cos (angle) - y * sin(angle), x * sine (angle) + y * cos(angle));
}

int rotation_key(int keysym, t_data *data)
{
    if (keysym == XK_Left)
    {
        data->player.angle -= 4 * PI / 180; //10.0f;
		//data->player.angle = FixAng(data->player.angle);
		//new_direction_rotation(data);
        draw_minimap_player(data);
    }
    else if (keysym == XK_Right)
	{
		data->player.angle += 4 * PI / 180; //10.0f;
		//data->player.angle = FixAng(data->player.angle);
		//new_direction_rotation(data);
        draw_minimap_player(data);
	}
    return (0);
} */

int    handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_loop_end(data->mlx_ptr);
    else if (keysym == XK_w)
    {
		new_direction_up(data);
        draw_minimap_player(data);
    }
    else if (keysym == XK_a)
    {
        new_direction_left(data);
        draw_minimap_player(data);
    }
    else if (keysym == XK_s)
    {
		new_direction_down(data);
        draw_minimap_player(data);
    }
    else if (keysym == XK_d)
    {
        new_direction_right(data);
        draw_minimap_player(data);
    }
    rotation_key(keysym, data);
    return (0);
}

/* int rotation_key(int keysym, t_data *data)
{
    // if (keysym == XK_braceleft) //XK_Leftarrow) //XK_Pointer_Left) //XK_Left) //XK_KP_Left)
	if (keysym == XK_Left) //XK_KP_Left)
    {
        // data->player.angle -= 0.5;
        // if (data->player.angle < 0)
        //     data->player.angle += 2 * PI;
        // data->player.fx = cos(data->player.angle) * 5;
        // data->player.fy = -sin(data->player.angle) * 5;
		data->player.angle -= 5;
		data->player.angle = FixAng(data->player.angle);
		new_direction(data);
        draw_minimap_player(data);
    }
    else if (keysym == XK_Right)
	{
		// data->player.angle += 0.5;
        // if (data->player.angle > 2 * PI)
        //     data->player.angle -= 2 * PI;
        // data->player.fx = cos(data->player.angle) * 5;
        // data->player.fy = -sin(data->player.angle) * 5;
		data->player.angle += 5;
		data->player.angle = FixAng(data->player.angle);
		new_direction(data);
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
	}
    return (0);
} */

/* int    handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_loop_end(data->mlx_ptr);
    else if (keysym == XK_w)
    {
		//data->player.y -= (TEXTURE_SIZE / 16);
         // data->player.y -= (TEXTURE_SIZE / 16);
        // data->player.x += data->player.fx;
        // data->player.y += data->player.fy;
		// data->player.x += data->player.fx * 5;
		// data->player.y += data->player.fy * 5;
        //if (data->config->map[(int)data->player.y][(int)data->player.x] != '1')
		new_direction_up(data);
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    else if (keysym == XK_a)
    {
        //data->player.x -= (TEXTURE_SIZE / 16);
        // data->player.angle -= 5;
		// data->player.angle = FixAng(data->player.angle);
        // data->player.angle = FixAng(data->player.angle);
		// data->player.fx = cos(deg_to_rad(data->player.angle));
		// data->player.fy = -sin(deg_to_rad(data->player.angle));
		// data->player.x = cos(deg_to_rad(data->player.angle));
		// data->player.y = -sin(deg_to_rad(data->player.angle));
        // data->player.rx = cos(data->player.angle) * 5;
        // data->player.ry = sin(data->player.angle) * 5;
		new_direction(data);
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    else if (keysym == XK_s)
    {
        //data->player.y += (TEXTURE_SIZE / 16);
        // data->player.x -= data->player.fx;
        // data->player.y -= data->player.fy;
		// data->player.x -= data->player.fx * 5;
		// data->player.y -= data->player.fy * 5;
		new_direction_down(data);
		// data->player.x -= data->player.x * 5;
		// data->player.y -= data->player.y * 5;
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    else if (keysym == XK_d)
    {
        //data->player.x += (TEXTURE_SIZE / 16);
        // data->player.angle += 5;
		// data->player.angle = FixAng(data->player.angle);
        // data->player.angle = FixAng(data->player.angle);
		// data->player.fx = cos(deg_to_rad(data->player.angle));
		// data->player.fy = -sin(deg_to_rad(data->player.angle));
        // // data->player.rx = cos(data->player.angle) * 5;
        // // data->player.ry = sin(data->player.angle) * 5;
		new_direction(data);
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    rotation_key(keysym, data);
    return (0);
} */

/* int    handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_loop_end(data->mlx_ptr);
    else if (keysym == XK_w)
    {
        // data->player.y -= (TEXTURE_SIZE / 16);
        // data->player.x += data->player.fx;
        // data->player.y += data->player.fy;
		data->player.x += data->player.fx * 5;
		data->player.y += data->player.fy * 5;
        //if (data->config->map[(int)data->player.y][(int)data->player.x] != '1')
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    else if (keysym == XK_a)
    {
        //data->player.x -= (TEXTURE_SIZE / 16);
        data->player.angle -= 0.5;
        data->player.angle = FixAng(data->player.angle);
		data->player.fx = cos(deg_to_rad(data->player.angle));
		data->player.fy = -sin(deg_to_rad(data->player.angle));
        // data->player.rx = cos(data->player.angle) * 5;
        // data->player.ry = sin(data->player.angle) * 5;
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    else if (keysym == XK_s)
    {
        //data->player.y += (TEXTURE_SIZE / 16);
        // data->player.x -= data->player.fx;
        // data->player.y -= data->player.fy;
		data->player.x -= data->player.fx * 5;
		data->player.y -= data->player.fy * 5;
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    else if (keysym == XK_d)
    {
        //data->player.x += (TEXTURE_SIZE / 16);
        data->player.angle += 0.5;
        data->player.angle = FixAng(data->player.angle);
		data->player.fx = cos(deg_to_rad(data->player.angle));
		data->player.fy = -sin(deg_to_rad(data->player.angle));
        // data->player.rx = cos(data->player.angle) * 5;
        // data->player.ry = sin(data->player.angle) * 5;
        draw_minimap_player(data);
        // draw_minimap_player_bis(data);
    }
    //rotation_key(keysym, data);
    return (0);
} */

/* int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	else if (keysym == XK_w)
	{
		data->player.y -= (TEXTURE_SIZE / 16);
		//if (data->config->map[(int)data->player.y][(int)data->player.x] != '1')
		draw_minimap_player(data);
	}
	else if (keysym == XK_a)
	{
		data->player.x -= (TEXTURE_SIZE / 16);
		draw_minimap_player(data);
	}
	else if (keysym == XK_s)
	{
		data->player.y += (TEXTURE_SIZE / 16);
		draw_minimap_player(data);
	}
	else if (keysym == XK_d)
	{
		data->player.x += (TEXTURE_SIZE / 16);
		draw_minimap_player(data);
	}
	
	return (0);
} */

/* int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	else if (keysym == XK_w)
	{
		data->player.y += 64;
		draw_player(data, data->player.x, data->player.y);
	}
	else if (keysym == XK_a)
	{
		data->player.x -= 64;
		draw_player_move(data, data->player.x, data->player.y);
	}
	else if (keysym == XK_s)
	{
		data->player.y += 64;
		draw_player_move(data, data->player.x, data->player.y);
	}
	else if (keysym == XK_d)
	{
		data->player.x -= 64;
		draw_player_move(data, data->player.x, data->player.y);
	}
	
	return (0);
} */
