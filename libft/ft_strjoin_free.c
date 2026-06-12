/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:19:50 by mbatty            #+#    #+#             */
/*   Updated: 2025/09/09 11:31:25 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*dest;
	size_t	len;

	if (!s1 || !s2)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (0);
	}
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	dest = malloc(len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, len);
	ft_strlcat(dest, s2, len);
	free(s1);
	free(s2);
	return ((char *)dest);
}
