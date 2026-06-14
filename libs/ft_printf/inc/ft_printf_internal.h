/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:58:40 by mbatty            #+#    #+#             */
/*   Updated: 2025/11/05 13:56:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include "ft_printf.h"
# include <unistd.h>

# define NULL_STRING	"(null)"
# define NIL_STR		"(nil)"
# define LOWER_HEX		"0123456789abcdef"
# define UPPER_HEX		"0123456789ABCDEF"

int	ft_putnbr(long n);
int	ft_putnbr_hex(long n, char *set);
int	ft_putadress(unsigned long int n);

int	ft_putchar(char c);
int	ft_putstr(char *str);

#endif
