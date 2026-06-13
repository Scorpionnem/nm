/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:29:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/13 17:01:26 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "ctx.h"

static void	swap(t_sym *s1, t_sym *s2)
{
	t_sym	tmp;

	ft_memcpy(&tmp, s1, sizeof(t_sym));
	ft_memcpy(s1, s2, sizeof(t_sym));
	ft_memcpy(s2, &tmp, sizeof(t_sym));
}

static int	partition(t_sym *arr, int reverse, int low, int high)
{
	t_sym pivot = arr[high];

	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		int	do_swap = reverse ? ft_strcmp(arr[j].name, pivot.name) > 0 : ft_strcmp(arr[j].name, pivot.name) < 0;
		if (do_swap)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	sort_syms(t_sym *arr, int reverse, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, reverse, low, high);

		sort_syms(arr, reverse, low, pi - 1);
		sort_syms(arr, reverse, pi + 1, high);
	}
}
