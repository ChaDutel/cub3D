/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_search_type.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:46:23 by maxperei          #+#    #+#             */
/*   Updated: 2022/11/29 18:58:17 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_search_type(va_list ap, const char *fmt)
{
	if (*fmt == 'c')
		return (ft_print_char(ap));
	if (*fmt == 's')
		return (ft_print_string(ap));
	if (*fmt == 'p')
		return (ft_print_pointer(ap));
	if (*fmt == 'd' || *fmt == 'i')
		return (ft_print_decimal(ap));
	if (*fmt == 'u')
		return (ft_print_unsigned(ap));
	if (*fmt == 'x')
		return (ft_print_smallhex(ap));
	if (*fmt == 'X')
		return (ft_print_bighex(ap));
	if (*fmt == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	else
	{
		ft_putchar(*fmt);
		return (1);
	}
}
