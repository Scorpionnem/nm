/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:11:09 by mbatty            #+#    #+#             */
/*   Updated: 2024/10/15 08:54:34 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		count++;
	}
	while (nb)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

static char	*fill_number(char *tab, long int nb, int i)
{
	if (nb != 0)
		i--;
	if (nb == 0 || nb == -0)
		tab[0] = '0';
	if (nb < 0)
	{
		tab[0] = '-';
		nb = nb * -1;
		while (i > 0)
		{
			tab[i] = (nb % 10 + '0');
			nb = nb / 10;
			i--;
		}
	}
	else
	{
		while (i >= 0 && nb != 0)
		{
			tab[i] = (nb % 10 + '0');
			nb = nb / 10;
			i--;
		}
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;

	i = nb_len(n);
	tab = malloc((i + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	tab[i] = '\0';
	return (fill_number(tab, (long int)n, i));
}
