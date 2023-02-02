/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charline <charline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:45:04 by charline          #+#    #+#             */
/*   Updated: 2023/02/02 22:57:50 by charline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int add_tab_colors_values(t_config *config, char *str, int iter, int i)
{
    int values;

    values = ft_atoi(str);
    if (values > 255)
        return (error_msg("Error : Colors values are too big"));
    else if (values < 0)
        return (error_msg("Error : Colors values are too small"));
    config->colors[i][iter] = values;
    return (0);
}

/* static int  check_colors_values(t_config *config, int i, int j)
{
    int count;
    int nb_values;
    char *str;
    char *str_tmp;

    nb_values = 0;
    str = NULL;
    while (nb_values < 3)
    {
        count = 0;
        while (config->elems[i][j] && config->elems[i][j] == ' ')
            j++;
        if (config->elems[i][j] < 0 || config->elems[i][j] > 9)
            return (error_msg("Error : Wrong colors values\n"))
        while (config->elems[i][j] && (config->elems[i][j] >= 0 && config->elems[i][j] <= 9))
        {
            str_tmp = str;
            str = ft_strjoin(str_tmp, config->elems[i][j]);
            free(str_tmp);
            j++;
        }
        while (config->elems[i][j] && config->elems[i][j] == ' ')
            j++;
        if (count != 2 && config->elems[i][j] != ',')
            return (error_msg("Error : Wrong colors values\n"));
        else if (count == 2 && config->elems[i][j] != '\0')
            return (error_msg("Error : Wrong last color values\n"));
        if (add_tab_colors_values(config, str, nb_values, i - 4) == -1)
        {
            free(str);
            return (-1);
        }
        free(str);
        nb_values++;
    }
    return (0);
} */

/* static int  check_colors_values(t_config *config, int i, int j)
{
    int nb_values;
    char *str;
    char *str_tmp;

    nb_values = 0;
    while (nb_values < 3)
    {
        str = NULL;
        while (config->elems[i][j] && config->elems[i][j] == ' ')
            j++;
        if (config->elems[i][j] < 0 || config->elems[i][j] > 9)
            return (error_msg("Error : Wrong colors values\n"));
        while (config->elems[i][j] && (config->elems[i][j] >= 0 && config->elems[i][j] <= 9))
        {
            str_tmp = str;
            str = ft_strjoin(str_tmp, config->elems[i][j]);
            free(str_tmp);
            j++;
        }
        while (config->elems[i][j] && config->elems[i][j] == ' ')
            j++;
        if (nb_values != 2 && config->elems[i][j] != ',')
        {
            free(str);
            return (error_msg("Error : Wrong colors values\n"));
        }
        else if (nb_values == 2 && config->elems[i][j] != '\0')
        {
            free(str);
            return (error_msg("Error : Wrong last color values\n"));
        }
        if (add_tab_colors_values(config, str, nb_values, i - 4) == -1)
        {
            free(str);
            return (-1);
        }
        free(str);
        nb_values++;
    }
    return (0);
} */

static int  check_colors_values_norm(char c, char *str, int nb_values)
{
    if (nb_values != 2 && c != ',')
    {
        free(str);
        return (error_msg("Error : Wrong colors values\n"));
    }
    else if (nb_values == 2 && c != '\0')
    {
        free(str);
        return (error_msg("Error : Wrong last color values\n"));
    }
    return (0);
}


static int  check_colors_values(t_config *config, int i, int j)
{
    int nb_values;
    char *str;
    char *str_tmp;

    nb_values = 0;
    while (nb_values < 3)
    {
        str = NULL;
        while (config->elems[i][j] && config->elems[i][j] == ' ')
            j++;
        if (config->elems[i][j] < 0 || config->elems[i][j] > 9)
            return (error_msg("Error : Wrong colors values\n"));
        while (config->elems[i][j] && (config->elems[i][j] >= 0 && config->elems[i][j] <= 9))
        {
            str_tmp = str;
            str = char_join(str_tmp, config->elems[i][j]);
            if (!str)
            {
                free(str_tmp);
                return (error_msg("Error : Malloc failed\n"));
            }
            free(str_tmp);
            j++;
        }
        while (config->elems[i][j] && config->elems[i][j] == ' ')
            j++;
        if (check_colors_values_norm(config->elems[i][j], str, nb_values) == -1)
            return (-1);
        if (add_tab_colors_values(config, str, nb_values, i - 4) == -1)
        {
            free(str);
            return (-1);
        }
        free(str);
        nb_values++;
    }
    return (0);
}

static int  check_colors(t_config *config)
{
    int i;
    int j;
    
    i = 4;
    config->colors = malloc(sizeof(int *) * 2);
    if (!config->colors)
        return (error_msg("Error : malloc failed\n"));
    config->colors[0] = malloc(sizeof(int) * 3);
        return (error_msg("Error : malloc failed\n"));
    config->colors[1] = malloc(sizeof(int) * 3);
        return (error_msg("Error : malloc failed\n"));
    while (config->elems[i])
    {
        j = 1;
        // while (config->elems[i][j] && config->elems[i][j] == ' ')
        //     j++;
        if (check_colors_values(config, i, j) == -1)
            return (error_msg("Error : Wrong colors values\n"));
        i++;
    }
}

int	parse_elems(t_config *config)
{
    int fd;
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 2;
        while (config->elems[i][j] && config->elems[i][j] == ' ')
            j++;
        fd = open(&config->elems[i][j], O_RDONLY);
        if (fd == -1)
            return (error_msg("Error : Wrong texture path\n"));
        close(fd);
        i++;
    }
    if (check_colors(config) == -1)
        return (-1);
    return (0);
}