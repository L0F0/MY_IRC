/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** launch_client
*/

#include "lib.h"

int	check_select(char *str, t_client *client)
{
	int	c = 0;
	int	b = 0;

	str[strlen(str)] = '\0';
	for (int i = 0; str[i]; i++) {
		if (str[i] == ':') {
			client->addr = strndup(str, i);
		c = i;
			while  (str[c]) { 
				c++;
			}
			client->port_char = malloc(sizeof(char) * c + 1);
			for (int e = i+1; e < c; e++) {
				client->port_char[b] = str[e];
				b++;
			}
			client->port_char[b] = '\0';
			return (0);	
		}
	}
	return (1);
}

char	*check_is_server(char *str)
{
	char	*tmp;
	int	i = 8;

	if (strncmp(str, "/server", 7) == 0)
	{
		while (str[i])
			i++;
		tmp = malloc(sizeof(char) * i + 1);
		i = 8;
		for (int e = 0; str[i]; e++) {
			tmp[e] = str[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}
		
void	put_port(t_client *client)
{
	int	characters;
	size_t	bufsize = 100;
	char	*buffer;


	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}          
	while ((characters = getline(&buffer,&bufsize,stdin)) != -1)
	{
		buffer[characters] = '\0';
		epur_str(buffer);
		if ((buffer = check_is_server(buffer)) != NULL) {
			if (check_select(buffer, client) == 0)
				return ;
		}
	}
	return ;
}

void	write_on_fd(t_client *client)
{
	int     characters;
	size_t  bufsize = 100;
	char    *buffer;

	buffer = malloc(sizeof(char) * bufsize);
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
		}
	while ((characters = getline(&buffer,&bufsize,stdin)) != -1)
	{
		buffer[characters] = '\0';
		epur_str(buffer);
		write(client->fd, buffer, strlen(buffer));
	}
}

int	launch_client()
{
	t_client		*client;
	
	client = malloc(sizeof(t_client));
	put_port(client);
	client->port = atoi(client->port_char);
	client->pe = getprotobyname("TCP");
	if (!client->pe)
		return (1);
	client->fd = socket(AF_INET, SOCK_STREAM, client->pe->p_proto);
	if (client->fd == -1)
		return (1);
	client->s_in.sin_family = AF_INET;
	client->s_in.sin_port = htons(client->port);
	client->s_in.sin_addr.s_addr = inet_addr(client->addr);
	if (connect(client->fd, (struct sockaddr *)&client->s_in,
		    sizeof(struct sockaddr)) == -1)
		return (1);
	write_on_fd(client);
	return (0);
}
