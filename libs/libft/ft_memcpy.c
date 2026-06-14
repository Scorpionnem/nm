/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:40:26 by mbatty            #+#    #+#             */
/*   Updated: 2024/10/15 08:54:22 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdest;

	csrc = (unsigned char *) src;
	cdest = (unsigned char *) dest;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n > 0)
	{
		*cdest++ = *csrc++;
		n--;
	}
	return (dest);
}
