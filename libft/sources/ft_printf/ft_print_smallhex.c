/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_smallhex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:45:54 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 18:58:06 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static	int	ft_hexlen(unsigned int hex)
{
	int	len;

	if (hex == 0)
		return (1);
	len = 0;
	while (hex != 0)
	{
		hex /= 16;
		len++;
	}
	return (len);
}

static	void	ft_puthex(unsigned int unbr)
{
	if (unbr > 15)
		ft_puthex(unbr / 16);
	ft_putchar("0123456789abcdef"[unbr % 16]);
}

int	ft_print_smallhex(va_list ap)
{
	static int		len;
	unsigned int	hex;

	hex = va_arg(ap, unsigned int);
	len = ft_hexlen(hex);
	ft_puthex(hex);
	return (len);
}
