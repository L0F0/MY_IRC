/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "lib.h"

struct sockaddr_in	initial(struct sockaddr_in s_in, int port)
{
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	return (s_in);
}

t_server	*init_server(t_server *server, char **av)
{
	server->port = atoi(av[1]);
	return (server);
}
