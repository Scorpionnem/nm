/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:39:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/05 13:51:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int	ft_putnbr(long n)
{
	if (n < 0)
		return (write(1, "-", 1) + ft_putnbr(n * -1));
	if (n >= 0 && n <= 9)
		return (ft_putchar(n % 10 + '0'));
	return (ft_putnbr(n / 10) + ft_putnbr(n % 10));
}

int	ft_putnbr_hex(long n, char *set)
{
	if (n < 0)
		return (write(1, "-", 1) + ft_putnbr_hex(n * -1, set));
	if (n >= 0 && n <= 15)
		return (ft_putchar(set[n % 16]));
	return (ft_putnbr_hex(n / 16, set) + ft_putnbr_hex(n % 16, set));
}

static int	ft_putnbr_hex_u(unsigned long int n, char *set)
{
	if (n >= 0 && n <= 15)
		return (ft_putchar(set[n % 16]));
	return (ft_putnbr_hex_u(n / 16, set) + ft_putnbr_hex_u(n % 16, set));
}

int	ft_putadress(unsigned long int n)
{
	if (n == 0)
		return (ft_putstr(NIL_STR));
	return (ft_putstr("0x") + ft_putnbr_hex_u(n, LOWER_HEX));
}
