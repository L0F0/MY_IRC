/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "lib.h"

int	check_fd(int fd)
{
	if (fd == -1)
		return (FAIL);
	return (SUCCESS);
}

int	check_close(int fd)
{
	if (close(fd) == -1)
		return (FAIL);
	return (SUCCESS);
}

int	check_bind(int fd, const struct sockaddr * s_in, size_t s_in2)
{
	if (bind(fd, s_in, s_in2) == -1) {
		if (check_close(fd) == FAIL)
			return (FAIL);
		return (FAIL);
	}
	return (SUCCESS);
}

int	check_listen(int fd, int nb)
{
	if (listen(fd, nb) == -1) {
		if (check_close(fd) == FAIL)
			return (FAIL);
		return (FAIL);
	}
	return (SUCCESS);
}
