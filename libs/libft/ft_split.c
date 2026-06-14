/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:00:59 by mbatty            #+#    #+#             */
/*   Updated: 2025/09/07 20:13:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char sep)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			count++;
			while (str[i] != sep && str[i])
				i++;
		}
		else
			i++;
	}
	return ((int)count);
}

static int	word_len(char const *s, char sep)
{
	size_t	j;

	j = 0;
	while (s[j] != sep && s[j])
		j++;
	return (j);
}

static void	free_all(char **str, int index)
{
	while (index--)
		free(str[index]);
	free(str);
}

static char	**ft_fillsplit(char **str, const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && j < (size_t)count_words(s, c))
	{
		if (s[i] != c)
		{
			str[j] = ft_substr(s, i, word_len(&s[i], c));
			if (!str[j])
			{
				free_all(str, j);
				return (NULL);
			}
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		if (!s[i])
			break ;
		i++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**str;

	if (!s)
		return (0);
	str = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str = ft_fillsplit(str, s, c);
	if (!str)
		return (NULL);
	return (str);
}
