/*
** EPITECH PROJECT, 2018
** test2
** File description:
** test2
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int	handle_client(int cs1, int cs2)
{
	char	buff[521];
	int	len;
	int	len2;

	len = read(cs1, buff, 520);
	if (len == -1)
	{
		write(2, "Error on read\n", strlen("Error on read\n"));
		exit(1);
	}
	len2 = 0;
	while (len2 != len)
	{
		len = len - len2;
		len2 = write(cs2, buff + len2, len);
	}
	return (0);
}
       


int	main(int ac, char **av)
{
	struct protoent		*pe;
	int			fd;
	struct sockaddr_in	s_in;
	int			port;
	struct sockaddr_in	s_in_client;
	socklen_t		s_in_size;
	int			client1_fd;
	int			client2_fd;
	fd_set			readfds;
	int			error;

	if (ac != 2)
		return (1);
	s_in_size = sizeof(s_in_client);
	port = atoi(av[1]);
	pe = getprotobyname("TCP");
	if (!pe)
		return (1);
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return (1);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
	{
		if (close(fd) == -1)
			return (1);
		return (1);
	}
	if (listen(fd, 42) == -1)
	{
		if (close(fd) == -1)
			return (1);
		return (1);
	}
	client1_fd = accept(fd, (struct sockaddr *)&s_in_client, &s_in_size);
	client2_fd = accept(fd, (struct sockaddr *)&s_in_client, &s_in_size);
	if (client1_fd == -1 || client2_fd == -1)
	{
		if (close(fd) == -1)
			return (1);
		return (1);
	}
	error = 0;
	while (!error)
	{
		FD_ZERO(&readfds);
		FD_SET(client1_fd, &readfds);
		FD_SET(client2_fd, &readfds);
		if (select((client1_fd > client2_fd ? client1_fd : client2_fd) + 1, &readfds, NULL, NULL, NULL) == -1) {
			error = 1;
		}
		else {
			if (FD_ISSET(client1_fd, &readfds))
			{
				handle_client(client1_fd, client2_fd);
			}
			if (FD_ISSET(client2_fd, &readfds))
			{
				handle_client(client2_fd, client1_fd);
			}
		}
	}
	if (close(fd) == -1)
		return (1);
	if (close(client1_fd) == -1)
		return (1);
	if (close(client2_fd) == -1)
		return (1);
}
	
