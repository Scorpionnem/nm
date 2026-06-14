/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 22:06:28 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/14 11:34:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <endian.h>

#include "ctx.h"

int	parse_elf_header(t_ctx *ctx)
{
	Elf64_Ehdr	*hdr;
	int			class;
	int			data;

	if (ctx->map.size < sizeof(Elf64_Ehdr))
		return (ft_printf("ft_nm: %s: file too small\n", ctx->path), 0);

	hdr = ctx->map.addr;

	if (ft_memcmp(hdr->e_ident, ELFMAG, sizeof(ELFMAG) - 1))
	{
		return (ft_printf("ft_nm: %s: file format not recognized\n", ctx->path), -1);
	}

	if (hdr->e_ident[EI_VERSION] != 1)
		return (ft_printf("ft_nm: %s: invalid ELF version %d\n", ctx->path, hdr->e_ident[EI_VERSION]), -1);

	class = hdr->e_ident[EI_CLASS];
	if (class != ELFCLASS32 && class != ELFCLASS64)
		return (ft_printf("ft_nm: %s: invalid class %d\n", ctx->path, class), -1);
	ctx->is_x64 = class == ELFCLASS64;

	data = hdr->e_ident[EI_DATA];
	if (data != ELFDATA2LSB && data != ELFDATA2MSB)
		return (ft_printf("ft_nm: %s: invalid endianness %d\n", ctx->path, data), -1);
	ctx->is_little_endian = data == ELFDATA2LSB;

	int	type = ctx->is_little_endian ? le16toh(hdr->e_type) : be16toh(hdr->e_type);
	if (type != ET_REL && type != ET_EXEC && type != ET_DYN)
		return (ft_printf("ft_nm: %s: invalid object type %d\n", ctx->path, type), -1);

	int	machine = ctx->is_little_endian ? le16toh(hdr->e_machine) : be16toh(hdr->e_machine);
	if ((!ctx->is_x64 && machine != EM_386) || (ctx->is_x64 && machine != EM_X86_64))
		return (ft_printf("ft_nm: %s: invalid architecture %d\n", ctx->path, machine), -1);

	int version = ctx->is_little_endian ? le32toh(hdr->e_version) : be32toh(hdr->e_version);
	if (version != 1)
		return (ft_printf("ft_nm: %s: invalid ELF version %d\n", ctx->path, version), -1);

	return (0);
}
