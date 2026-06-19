/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 20:40:00 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/19 21:00:25 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

uint16_t	fix_u16_endian(uint16_t val, int val_endianness);
uint32_t	fix_u32_endian(uint32_t val, int val_endianness);
uint64_t	fix_u64_endian(uint64_t val, int val_endianness);
int16_t		fix_s16_endian(int16_t val, int val_endianness);
int32_t		fix_s32_endian(int32_t val, int val_endianness);
int64_t		fix_s64_endian(int64_t val, int val_endianness);
