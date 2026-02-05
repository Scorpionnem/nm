/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:27:19 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/05 15:10:11 by mbatty           ###   ########.fr       */
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

/*
open(2) close(2) mmap(2) munmap(2) write(2)
fstat(2) malloc(3) free(3) exit(3) perror(3)
strerror(1) getpagesize(2)
*/

int	ft_nm(char *path)
{
	int	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("ft_nm: '%s': %s\n", path, strerror(errno)), 0);

	struct stat	stats;
	if (fstat(fd, &stats) == -1)
	{
		close(fd);
		return (printf("ft_nm: '%s': %s\n", path, strerror(errno)), 0);
	}

	size_t	size = stats.st_size;
	void	*map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
	{
		close(fd);
		return (printf("ft_nm: '%s': %s\n", path, strerror(errno)), 0);
	}

	// parse_file(map, size);

	close(fd);
	munmap(map, size);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		return (ft_nm("a.out"));

	int	error = 0;

	for (int i = 1; i < ac; i++)
		error += ft_nm(av[i]);
	return (error == 0);
}
