/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 22:09:14 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/13 12:39:22 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#include "libft.h"

typedef struct s_map
{
	int			fd;
	void		*addr;
	uint64_t	size;
}	t_map;

typedef struct s_ctx
{
	int		print_path;

	int		is_x64;
	int		is_little_endian;

	char	*path;

	t_map	map;
}	t_ctx;

typedef struct	s_sym
{
	char		c;
	uint64_t	value;
	char		*name;
}	t_sym;

void	sort_syms(t_sym *arr, int low, int high);

int	parse_elf_header(t_ctx *ctx);

int	get_map(t_map *map, const char *path);
int	close_map(t_map *map);

int	parse_64_little_endian(t_ctx *ctx);

void	ft_itoa_hex(char *buf, uint32_t n);
