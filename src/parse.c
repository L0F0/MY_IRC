/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "lib.h"

void	parse_arg(char *str, int cs1, t_server *server)
{
	if(strncmp(str, "/server", 7) == 0)
		printf("server\n");
	else if(strncmp(str, "/nick", 5) == 0)
		getnickname(str, server, cs1);
	else if(strncmp(str, "/list", 5) == 0)
		printf("list\n");
	else if(strncmp(str, "/join", 5) == 0)
		join_chanel(str, cs1, server);
	else if(strncmp(str, "/part", 5) == 0)
		printf("part\n");
	else if(strncmp(str, "/users", 6) == 0)
		user_function(str, cs1, server);
	else if(strncmp(str, "/names", 6) == 0)
		printf("names\n");
	else if(strncmp(str, "$message", 8) == 0)
		printf("message\n");
	else if(strncmp(str, "/msg", 4) == 0)
		printf("msg\n");
	else if(strncmp(str, "/accept_file", 12) == 0)
		printf("accept_file\n");
	else
	printf("Bad command\n");
}
