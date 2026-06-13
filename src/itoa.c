/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 12:29:59 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/13 16:25:44 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#define LOWER_HEX		"0123456789abcdef"

static void	ft_itoa_hex_rec(char *buf, uint32_t n, uint32_t *i)
{
	if (n <= 15)
	{
		buf[*i] = LOWER_HEX[n % 16];
		(*i)++;
		return ;
	}
	ft_itoa_hex_rec(buf, n / 16, i);
	ft_itoa_hex_rec(buf, n % 16, i);
}

void	ft_itoa_hex(char *buf, uint32_t n)
{
	uint32_t	i = 0;

	ft_itoa_hex_rec(buf, n, &i);
}
