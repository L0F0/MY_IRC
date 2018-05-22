/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** launch_server
*/

#include "lib.h"

int     handle_server(int cs1)
{
	char    buff[521];
	int     len;
	int     len2;

	cs1 = cs1;
	len = read(0, buff, 520);
	if (len == -1)
	{
		write(2, "Error on read\n", strlen("Error on read\n"));
		exit(1);
	}
	len2 = 0;
	while (len2 != len)
	{
		len = len - len2;
		len2 = write(0, buff + len2, len);
		write(0, "\n", 1);
	}
	return (0);
}

int	delete_client(int fd, t_clientOnServer **allClient)
{	
	t_clientOnServer *tmp = *allClient;
	t_clientOnServer *theNext;

	if (tmp == NULL)
		return (1);
	if (tmp->client_fd == fd) { // Le premier
		tmp->value = -1;
		*allClient = tmp->next;
		free(tmp);
		return (1);
	}
	while (tmp->next != NULL && tmp->next->client_fd != fd)
		tmp = tmp->next;
	if (tmp == NULL)
		return (1);
	if (tmp->next->next == NULL) { //Le dernier 
		tmp->next->value = -2;
		free(tmp->next);
		tmp->next = NULL;
	}
	else { // Entre
		tmp->next->value = -3;
		theNext = tmp->next;
		tmp->next = theNext->next;
		free(theNext);
	}
	*allClient = tmp;
	return (0);
}

int     handle_client2(int cs1, t_server *server)
{
	char    buff[521];
	int     len;

	len = read(cs1, buff, 520);
	if (len == -1 || len == 0)
	{
		write(2, "Error on read\n", strlen("Error on read\n"));
		delete_client(cs1, &server->allClient);
	}
	write(0, buff, len);
	parse_arg(buff, server);
	write(0, "\n", 1);
	return (0);
}

/*
int     handle_client(t_server *server)
{
	t_clientOnServer *tmp = server->allClient;
	char    buff[521];
	int     len;
	int     len2;

	if (tmp == NULL)
		return (1);
	printf("Value de -> %d\n", tmp->value);
	while (tmp->next != NULL) {
		len = read(tmp->client_fd, buff, 520);
		if (len == -1 || len == 0)
		{
			//Ne pas oublier de supprimer ce client;
			write(2, "Error on read\n", strlen("Error on read\n"));
			write(0, "Error on read\n", strlen("Error on read\n"));
			//exit (1)
			return 1;
		}
		len2 = 0;
		while (len2 != len)
		{
			len = len - len2;
			len2 = write(server->fd, buff + len2, len);
		}
		tmp = tmp->next;
	}
	return (0);
}
*/
int	initTheServer(t_server *server, char **av)
{
	if (server == NULL)
		return (1);
	server->allClient = malloc(sizeof(t_clientOnServer));
	if (server->allClient == NULL)
		return (1);
	server->allClient->next = NULL;
	server->allClient->s_in_size = sizeof(server->allClient->s_in_client);
	server->port = atoi(av[1]);
	server->pe = getprotobyname("TCP");
	if (!server->pe)
		return (1);
	server->fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto);
	if (server->fd == -1)
		return (1);
	server->s_in.sin_family = AF_INET;
	server->s_in.sin_port = htons(server->port);
	server->s_in.sin_addr.s_addr = INADDR_ANY;
	if (initTheServerNext(server) == 1)
		return (1);
	return (0);
}

void	printAllClient(t_server *server)
{
	t_clientOnServer *tmp = server->allClient;

	printf("Value is Here2 -> %d\n", tmp->value);
	while (tmp != NULL) {
		printf("Value -> %d\n", tmp->value);
		tmp = tmp->next;
	}
}

int	new_client(t_server *server)
{
	t_clientOnServer *node;
	static int	id = 1;

	node = malloc(sizeof(t_clientOnServer));
	if (node == NULL)
		return (FAIL);
	node->client_fd =
		accept(server->fd, (struct sockaddr *)&node->s_in_client, &node->s_in_size);
	if (node->client_fd < 0) {
		free(node);
		return (FAIL);
	}
	node->value = id;
	node->next = server->allClient;
	server->allClient = node;
	id++;
	return (SUCCESS);
}

int	checkIfWrite(t_server *server)
{
	t_clientOnServer	*tmp = server->allClient;

	if (tmp == NULL)
		return (1);
	while (tmp != NULL) {
		if (FD_ISSET(tmp->client_fd, &server->readfd)) {
			handle_client2(tmp->client_fd, server);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	initTheServerNext(t_server *server)
{
	if (bind(server->fd, (const struct sockaddr *)&server->s_in, sizeof(server->s_in)) == -1) {
		if (close(server->fd) == -1)
			return (FAIL);
		return (FAIL);
	}
	if (listen(server->fd, 42) == -1) {
		if (close(server->fd) == -1)
			return (FAIL);
		return (FAIL);
	}
	server->tv.tv_sec = 1;
	server->tv.tv_usec = 1000;
	return (0);
}

int	launch_server(char **av)
{
	t_server		*server;
	t_clientOnServer	*client;

	server = malloc(sizeof(t_server));
	if (initTheServer(server, av) == FAIL)
		return (FAIL);
	while (42) {
		client = server->allClient;
		FD_ZERO(&server->readfd);
		FD_SET(server->fd, &server->readfd);
		while (client != NULL) {
			FD_SET(client->client_fd, &server->readfd);
			client = client->next;			
		}
//		select(server->fd + 1, &server->readfd, NULL, NULL, &server->tv);
		select(100 + 1, &server->readfd, NULL, NULL, &server->tv);
		//Faire ISSET sur tous les clients pour savoir si on a ecrit dedans !
		if (FD_ISSET(server->fd, &server->readfd)) {
			printf("Connexion !\n");
			new_client(server);
			//printAllClient(server);
		}
		checkIfWrite(server);
	}
	if (close(server->fd) == -1)
		return (FAIL);
	return (SUCCESS);
}
