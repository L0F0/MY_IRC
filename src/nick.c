/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "lib.h"

void	search_client(t_clientOnServer *client, int cs1, char *name)
{
	t_clientOnServer *tmp;

	tmp = client;
	while (tmp != NULL) {
		if (tmp->client_fd == cs1) {
			tmp->name = name;
		}
		tmp = tmp->next;
	}
}

int	get_command(char *str)
{
	int	i = 0;

	while(str[i] != '\0') {
		if (str[i] == ' ')
			return (i + 1);
		i++;
	}
	return (i);
}

void	getnickname(char *str, t_server *server, int cs1)
{
	char	*tmp;
	int	index1 = 0;
	int	index2 = 0;

	tmp = malloc(sizeof(char) * strlen(str) + 1);
	index2 = get_command(str);
	while(str[index2]) {
		tmp[index1] = str[index2];
		index1++;
		index2++;
		
	}
	tmp[index1] = '\0';
	search_client(server->allClient, cs1, tmp);
}
