#include <stdio.h>
#include <endian.h>
#include <stdint.h>

#define HOST_LITTLE_ENDIAN 1
#define HOST_BIG_ENDIAN 0

static int get_host_endianness(void)
{
	unsigned int x = 1;

	return (*(unsigned char *)&x);
}

static uint16_t	bswap16(uint16_t v)
{
	return ((v << 8) | (v >> 8 ));
}

static uint32_t	bswap32(uint32_t v)
{
	v = ((v << 8) & 0xFF00FF00 ) | ((v >> 8) & 0xFF00FF ); 
	return ((v << 16) | (v >> 16));
}

static uint64_t	bswap64(uint64_t v)
{
	v = ((v << 8) & 0xFF00FF00FF00FF00ULL ) | ((v >> 8) & 0x00FF00FF00FF00FFULL );
	v = ((v << 16) & 0xFFFF0000FFFF0000ULL ) | ((v >> 16) & 0x0000FFFF0000FFFFULL );
	return ((v << 32) | (v >> 32));
}

uint16_t	fix_u16_endian(uint16_t val, int val_endianness)
{
	if (val_endianness == get_host_endianness())
		return (val);
	return (bswap16(val));
}

uint32_t	fix_u32_endian(uint32_t val, int val_endianness)
{
	if (val_endianness == get_host_endianness())
		return (val);
	return (bswap32(val));
}

uint64_t	fix_u64_endian(uint64_t val, int val_endianness)
{
	if (val_endianness == get_host_endianness())
		return (val);
	return (bswap64(val));
}

int16_t	fix_s16_endian(int16_t val, int val_endianness)
{
	return (fix_u16_endian(val, val_endianness));
}

int32_t	fix_s32_endian(int32_t val, int val_endianness)
{
	return (fix_u32_endian(val, val_endianness));
}

int64_t	fix_s64_endian(int64_t val, int val_endianness)
{
	return (fix_u64_endian(val, val_endianness));
}
