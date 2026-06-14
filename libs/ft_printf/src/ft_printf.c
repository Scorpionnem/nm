/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:54:11 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/05 14:04:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	if (!str)
		return (ft_putstr(NULL_STRING));
	return (write(1, str, ft_strlen(str)));
}

static int	ft_exec_flag(va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int), LOWER_HEX));
	if (c == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), UPPER_HEX));
	if (c == 'p')
		return (ft_putadress(va_arg(args, unsigned long int)));
	if (c == '%')
		return (ft_putchar('%'));
	return (ft_putchar('%') + ft_putchar(c));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		res;

	if (!str)
		return (-1);
	res = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			res += ft_exec_flag(args, *(str + 1));
			str += 2;
			continue ;
		}
		res += write(1, str++, 1);
	}
	va_end(args);
	return (res);
}
