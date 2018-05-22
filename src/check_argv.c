/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** check_argv.c
*/


#include "lib.h"

int	check_argv_for_server(char **av)
{
	if (strcmp(av[1], "-help") == SUCCESS) {
		Usage();
		return (FAIL);
	}
	if (atoi(av[1]) == SUCCESS) {
		Usage();
		return (FAIL);
	}
	return (SUCCESS);
}
