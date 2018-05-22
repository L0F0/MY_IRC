/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** main
*/

#include "lib.h"


void	Usage()
{
	printf("USAGE: ./server port\n");
}

int	main(int ac, char **av)
{
	if (strcmp(av[0], "./server") == SUCCESS) {
		if (ac < 2) {
			Usage();
			return (FAIL);
		}
		if (check_argv_for_server(av) == FAIL)
			return (FAIL);
		launch_server(av);
	}
	else {
		return (launch_client());
	}
	return (SUCCESS);
}
