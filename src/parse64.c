/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:02:22 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/13 17:11:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ctx.h"

static char	get_sym_char_64(Elf64_Sym *sym, Elf64_Shdr *section_hdr)
{
	uint8_t	bind = ELF64_ST_BIND(sym->st_info);
	switch (sym->st_shndx)
	{
		case SHN_UNDEF:
			return (bind == STB_WEAK ? 'w' : 'U');
		case SHN_ABS:
			return (bind == STB_GLOBAL ? 'A' : 'a');
		case SHN_COMMON:
			return (bind == STB_GLOBAL ? 'C' : 'c');
	}
	if (bind == STB_WEAK)
		return ('W');

	unsigned int	type = section_hdr[sym->st_shndx].sh_type;
	unsigned int	flags = section_hdr[sym->st_shndx].sh_flags;

	char	res = '?';

	if (flags & SHF_EXECINSTR)
		res = 'T';
	else if (flags & SHF_ALLOC && type == SHT_NOBITS)
		res = 'B';
	else if (flags & SHF_ALLOC && flags & SHF_WRITE)
		res = 'D';
	else if (flags & SHF_ALLOC && !(flags & SHF_WRITE))
		res = 'R';
	else
		return ('?');

	if (bind != STB_GLOBAL)
		res += 32;
	return (res);
}

static void	print_syms_64(t_sym *syms_arr, uint64_t syms_count)
{
	for (uint64_t i = 0; i < syms_count; i++)
	{
		char	buf1[17] = {0};
		ft_itoa_hex(buf1, syms_arr[i].value);

		char	buf2[17] = "0000000000000000";
		ft_memcpy(buf2 + (16 - strlen(buf1)), buf1, strlen(buf1));

		if (syms_arr[i].show_value)
			printf("%s %c %s\n", buf2, syms_arr[i].c, syms_arr[i].name);
		else
			printf("                 %c %s\n", syms_arr[i].c, syms_arr[i].name);
	}
}

int	parse_64(t_ctx *ctx)
{
	Elf64_Ehdr	*elf_hdr = (Elf64_Ehdr *)ctx->map.addr;

	Elf64_Shdr	*section_hdr = (Elf64_Shdr *)((char *)ctx->map.addr + elf_hdr->e_shoff);

	Elf64_Shdr	*symtab_hdr = NULL;

	int	found = 0;
	for (int i = 0; i < elf_hdr->e_shnum; i++)
		if (section_hdr[i].sh_type == SHT_SYMTAB)
		{
			symtab_hdr = &section_hdr[i];
			found = 1;
		}

	if (!found)
		return (printf("ft_nm: %s: no symbols\n", ctx->path), -1);

	Elf64_Shdr	*string_hdr = &section_hdr[symtab_hdr->sh_link];
	Elf64_Sym	*symbols = (Elf64_Sym *)((char *)ctx->map.addr + symtab_hdr->sh_offset);

	size_t		nsyms = symtab_hdr->sh_size / sizeof(Elf64_Sym);

	char	*strings = (char *)ctx->map.addr + string_hdr->sh_offset;

	t_sym	*syms_arr = malloc(nsyms * sizeof(t_sym));
	int		sym_idx = 0;

	for (size_t i = 1; i < nsyms; i++)
	{
		Elf64_Sym	*sym = &symbols[i];

		char *name = strings + sym->st_name;

		if (name[0] == 0
			|| (!ctx->show_debug_syms && ELF64_ST_TYPE(sym->st_info) == STT_FILE)
			|| (!ctx->show_debug_syms && ELF64_ST_TYPE(sym->st_info) == STT_SECTION))
			continue ;

		syms_arr[sym_idx++] = (t_sym){
			.c = get_sym_char_64(sym, section_hdr),
			.value = sym->st_value,
			.name = name,
			.show_value = sym->st_shndx != SHN_UNDEF
		};
	}

	if (!ctx->no_sort)
		sort_syms(syms_arr, ctx->reverse_sort, 0, sym_idx - 1);

	if (ctx->print_path)
		printf("\n%s:\n", ctx->path);

	print_syms_64(syms_arr, sym_idx);

	free(syms_arr);
	return (0);
}
