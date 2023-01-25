/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:45:41 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 18:57:56 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static	void	ft_putnbr(int nbr)
{
	unsigned int	unbr;

	if (nbr < 0)
	{
		write(1, "-", 1);
		unbr = -nbr;
	}
	else
		unbr = nbr;
	if (unbr > 9)
		ft_putnbr(unbr / 10);
	ft_putchar(unbr % 10 + 48);
}

int	ft_print_decimal(va_list ap)
{
	int		len;
	int		nbr;

	nbr = va_arg(ap, int);
	len = ft_nbrlen(nbr);
	if (nbr < 0)
		len++;
	ft_putnbr(nbr);
	return (len);
}
