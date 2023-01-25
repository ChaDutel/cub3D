/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:36:40 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 18:59:51 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static	int	ft_isspace(int c)
{
	if (c == 32 || (c <= 13 && c >= 9))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	short		minus;
	long long	nbr;

	minus = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * minus);
}
