/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:27:19 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/14 11:36:13 by mbatty           ###   ########.fr       */
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
		return (ft_printf("ft_nm: %s: endianness not supported\n", ctx->path), -1);

	if (ctx->is_x64)	
		parse_64(ctx);
	else
		parse_32(ctx);

	close_map(&ctx->map);
	return (0);
}

#define HELP_STRING "\
\n\
Usage:\n  ./ft_nm [option(s)] [file(s)]\n\
\n\
Options:\n\
  -h\tshow help message and exit\n\
  -a\tshow debug suymbols\n\
  -g\tshow extern only\n\
  -u\tshow undefined only\n\
  -r\treverse sort\n\
  -p\tno sort\n\
\n\
"

int	parse_opt(t_ctx *ctx, int *ac, char ***av)
{
	int	i = -1;
	int	dump = 0;

	*ac = 0;
	(*av)++;
	while ((*av)[++i])
	{
		char	*arg = (*av)[i];

		if (!ft_strcmp("-h", arg))
			return (ft_printf(HELP_STRING), -1);
		else if (!ft_strcmp("-a", arg))
			ctx->show_debug_syms = 1;
		else if (!ft_strcmp("-p", arg))
			ctx->no_sort = 1;
		else if (!ft_strcmp("-r", arg))
			ctx->reverse_sort = 1;
		else if (!ft_strcmp("-g", arg))
			ctx->show_extern_only = 1;
		else if (!ft_strcmp("-u", arg))
			ctx->show_undefined_only = 1;
		else
		{
			(*ac)++;
			(*av)[dump++] = (*av)[i];
		}
	}
	(*av)[dump] = NULL;
	return (0);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_ctx));

	if (parse_opt(&ctx, &ac, &av) == -1)
		return (-1);
	
	ctx.print_path = ac > 2;

	int	error = 0;

	for (int i = 0; i < ac; i++)
		error = (ft_nm(&ctx, av[i]) || error != 0) ? 1 : 0;

	return (error);
}
