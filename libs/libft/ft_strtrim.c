/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:29:03 by mbatty            #+#    #+#             */
/*   Updated: 2024/10/15 08:53:55 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_start(char const *str, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[i] && str[j])
	{
		if (str[j] == set[i])
		{
			j++;
			i = -1;
		}
		i++;
	}
	return (j);
}

static int	count_end(char const *str, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (j > count_start(str, set) && set[i])
	{
		if (str[j] == set[i])
		{
			j--;
			i = -1;
		}
		i++;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*str;	

	if (!s1 || !set)
		return (0);
	i = 0;
	start = count_start(s1, set);
	end = count_end(s1, set);
	str = malloc((end - start + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (start <= end)
	{
		str[i] = s1[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
