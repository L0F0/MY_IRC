/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "lib.h"

int	load_server(int port)
{
	int	fd;
	struct protoent *pe;
	struct sockaddr_in addr;

	pe = getprotobyname("TCP");
	addr = initial(addr, port);
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (check_fd(fd) == FAIL)
		return (FAIL);
	if (check_bind(fd, (const struct sockaddr *)&addr, sizeof (addr)) == FAIL)
		return (FAIL);
	if (check_listen(fd, 420) == FAIL)
		return (FAIL);
	return (fd);
}

int	server(char **av)
{
	t_server		*server;
	//t_client		*client;
	//struct sockaddr_in	sin_client;
	//int			sin_client_size;

	server = malloc(sizeof(t_server));
	//sin_client_size = sizeof(sin_client);
	init_server(server, av);
	//init_client(client, av);
	if ((server->fd = load_server(server->port)) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
