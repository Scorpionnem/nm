/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 22:26:22 by mbatty            #+#    #+#             */
/*   Updated: 2026/06/14 11:34:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "ctx.h"

int	get_map(t_map *map, const char *path)
{
	map->fd = open(path, O_RDONLY);
	if (map->fd == -1)
		return (ft_printf("open: '%s': %s\n", path, strerror(errno)), -1);

	struct stat	stats;
	if (fstat(map->fd, &stats) == -1)
	{
		close(map->fd);
		return (ft_printf("fstat: '%s': %s\n", path, strerror(errno)), -1);
	}

	map->size = stats.st_size;
	map->addr = mmap(NULL, map->size, PROT_READ, MAP_PRIVATE, map->fd, 0);
	if (map->addr == MAP_FAILED)
	{
		close(map->fd);
		return (ft_printf("mmap: %s: %s\n", path, strerror(errno)), -1);
	}
	return (0);
}

int	close_map(t_map *map)
{
	close(map->fd);
	munmap(map->addr, map->size);
	return (0);
}
