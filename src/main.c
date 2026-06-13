/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:27:19 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/13 12:39:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>
#include <elf.h>
#include <unistd.h>
#include <endian.h>

#include "ctx.h"

int	ft_nm(t_ctx *ctx, char *path)
{
	ctx->path = path;

	if (get_map(&ctx->map, path) == -1)
		return (-1);

	if (parse_elf_header(ctx) == -1)
	{
		close_map(&ctx->map);
		return (-1);
	}

	if (!ctx->is_little_endian)
		return (printf("ft_nm: endianness not supported\n"), -1);

	if (ctx->is_x64)	
		parse_64_little_endian(ctx);
	// else
	// 	parse_32_little_endian(ctx);

	close_map(&ctx->map);
	return (0);
}

int	main(int ac, char **av)
{
	t_ctx	ctx = {0};

	ctx.print_path = ac > 2;

	int	error = 0;

	for (int i = 1; i < ac; i++)
		error = (error != 0 || ft_nm(&ctx, av[i]) != 0) ? 1 : 0;
	return (error);
}
