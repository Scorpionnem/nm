/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:30:32 by mbatty            #+#    #+#             */
/*   Updated: 2024/10/15 08:54:07 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;

	if (size == 0)
		return (ft_strlen(src));
	len_dest = ft_strlen(dest);
	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i] != '\0' && (i + j + 1) < size)
	{
		dest[i + j] = src[i];
		i++;
	}
	if (i < size)
		dest[i + j] = '\0';
	if (size <= len_dest)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + len_dest);
}
