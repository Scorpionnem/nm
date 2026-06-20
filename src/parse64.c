/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:02:22 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/20 18:56:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ctx.h"
#include "endian.h"

static char	get_sym_char_64(Elf64_Sym *sym, Elf64_Shdr *section_hdr, int is_little_endian)
{
	uint8_t bind = ELF64_ST_BIND(sym->st_info);
	uint8_t st_type = ELF64_ST_TYPE(sym->st_info);

	switch (sym->st_shndx)
	{
		case SHN_UNDEF:
		{
			if (bind == STB_WEAK)
				return (st_type == STT_OBJECT ? 'v' : 'w');
			return ('U');
		}
		case SHN_ABS:
			return (bind == STB_GLOBAL ? 'A' : 'a');
		case SHN_COMMON:
			return (bind == STB_GLOBAL ? 'C' : 'c');
	}

	if (bind == STB_WEAK)
		return (st_type == STT_OBJECT ? 'V' : 'W');

	uint32_t	type = fix_u32_endian(section_hdr[sym->st_shndx].sh_type, is_little_endian);
	uint32_t	flags = fix_u32_endian(section_hdr[sym->st_shndx].sh_flags, is_little_endian);

	char res;

	if (flags & SHF_EXECINSTR)
		res = 'T';
	else if ((flags & SHF_ALLOC) && type == SHT_NOBITS)
		res = 'B';
	else if ((flags & SHF_ALLOC) && (flags & SHF_WRITE))
		res = 'D';
	else if (flags & SHF_ALLOC)
		res = 'R';
	else
		res = '?';

	if (bind == STB_LOCAL)
		res += 32;

	return (res);
}

static void	print_syms_64(t_sym *syms_arr, uint32_t syms_count)
{
	for (uint32_t i = 0; i < syms_count; i++)
	{
		if (!syms_arr[i].print)
			continue ;

		char	buf1[17];
		ft_memset(buf1, 0, sizeof(buf1));
		ft_itoa_hex(buf1, syms_arr[i].value);

		char	buf2[17] = "0000000000000000";
		ft_memcpy(buf2 + (16 - ft_strlen(buf1)), buf1, ft_strlen(buf1));

		if (syms_arr[i].show_value)
			ft_printf("%s %c %s\n", buf2, syms_arr[i].c, syms_arr[i].name);
		else
			ft_printf("                 %c %s\n", syms_arr[i].c, syms_arr[i].name);
	}
}

#define CHECK_INVALID_BOUNDS(address) ((void*)address > ctx->map.addr + ctx->map.size)

int	parse_64(t_ctx *ctx)
{
	Elf64_Ehdr	*elf_hdr = (Elf64_Ehdr *)ctx->map.addr;

	Elf64_Shdr	*section_hdr = (Elf64_Shdr *)((char *)ctx->map.addr + fix_u64_endian(elf_hdr->e_shoff, ctx->is_little_endian));
	if (CHECK_INVALID_BOUNDS(section_hdr))
		return (ft_printf("ft_nm: %s: file format not recognized\n", ctx->path), -1);

	Elf64_Shdr	*symtab_hdr = NULL;

	int	found = 0;
	for (int i = 0; i < fix_u16_endian(elf_hdr->e_shnum, ctx->is_little_endian); i++)
		if (fix_u32_endian(section_hdr[i].sh_type, ctx->is_little_endian) == SHT_SYMTAB)
		{
			symtab_hdr = &section_hdr[i];
			found = 1;
		}

	if (!found)
		return (ft_printf("ft_nm: %s: no symbols\n", ctx->path), -1);

	Elf64_Shdr	*string_hdr = &section_hdr[symtab_hdr->sh_link];
	Elf64_Sym	*symbols = (Elf64_Sym *)((char *)ctx->map.addr + fix_u32_endian(symtab_hdr->sh_offset, ctx->is_little_endian));
	if (CHECK_INVALID_BOUNDS(symbols))
		return (ft_printf("ft_nm: %s: file format not recognized\n", ctx->path), -1);

	size_t		nsyms = fix_u64_endian(symtab_hdr->sh_size, ctx->is_little_endian) / sizeof(Elf64_Sym);

	char	*strings = (char *)ctx->map.addr + fix_u64_endian(string_hdr->sh_offset, ctx->is_little_endian);
	if (CHECK_INVALID_BOUNDS(strings))
		return (ft_printf("ft_nm: %s: file format not recognized\n", ctx->path), -1);

	t_sym	*syms_arr = malloc(nsyms * sizeof(t_sym));
	int		sym_idx = 0;

	for (size_t i = 1; i < nsyms; i++)
	{
		Elf64_Sym	*sym = &symbols[i];

		char *name = strings + fix_u32_endian(sym->st_name, ctx->is_little_endian);
		if (CHECK_INVALID_BOUNDS(name))
		{
			free(syms_arr);
			return (ft_printf("ft_nm: %s: file format not recognized\n", ctx->path), -1);
		}

		if ((!ctx->show_debug_syms && name[0] == 0)
			|| (!ctx->show_debug_syms && ELF64_ST_TYPE(sym->st_info) == STT_FILE)
			|| (!ctx->show_debug_syms && ELF64_ST_TYPE(sym->st_info) == STT_SECTION))
			continue ;

		char	sym_c = get_sym_char_64(sym, section_hdr, ctx->is_little_endian);

		int	print = 1;
		if (fix_u16_endian(sym->st_shndx, ctx->is_little_endian) != SHN_UNDEF && ctx->show_undefined_only)
			print = 0;
		if ((sym_c >= 'a' && sym_c <= 'z' && sym_c != 'w') && ctx->show_extern_only)
			print = 0;

		syms_arr[sym_idx++] = (t_sym){
			.c = sym_c,
			.value = fix_u64_endian(sym->st_value, ctx->is_little_endian),
			.name = name,
			.show_value = fix_u16_endian(sym->st_shndx, ctx->is_little_endian) != SHN_UNDEF,
			.print = print
		};
	}

	if (!ctx->no_sort)
		sort_syms(syms_arr, ctx->reverse_sort, 0, sym_idx - 1);

	if (ctx->print_path)
		ft_printf("\n%s:\n", ctx->path);

	print_syms_64(syms_arr, sym_idx);

	free(syms_arr);
	return (0);
}
