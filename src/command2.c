/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** command2.c
*/

#include "lib.h"

void	print_chanel(t_chanel *chanel)
{
	t_chanel	*tmp = chanel;

	printf("Persone\n");
	while (tmp != NULL) {
		printf("Chanel -> %s | Id -> %d\n", tmp->name, tmp->id);
		tmp = tmp->next;
	}
}

t_chanel *create_chanel(char *name)
{
	static int	id = 1;
	t_chanel *new = malloc(sizeof(t_chanel));

	if (new == NULL)
		return (NULL);
        new->name = strdup(name);
	new->id = id;
	printf("Name -> %s\n", name);
	id++;
	new->next = NULL;
	return (new);
}

int	checkIfChanel(char *str, t_chanel **chanel, int cs1, t_server **server)
{
	t_chanel	*tmp = *chanel;

	if (tmp == NULL) {
		*chanel = create_chanel(str);
		if (*chanel == NULL)
			return (FAIL);
		return (SUCCESS);
	}
	cs1 = cs1;
	server = server;
	while (tmp != NULL) {
		if (strcmp(tmp->name, str) == 0) {
			
			return (0);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp->next = create_chanel(str);
	if (tmp->next == NULL)
		return (FAIL);
	return (SUCCESS);
}

void	join_chanel(char *str, int cs1, t_server *server)
{
	char	*arg;

	arg = word_after_space(str);
	checkIfChanel(arg, &server->chanel, cs1, &server);
	print_chanel(server->chanel);
	printf("arg -> %s\n", arg);
}
