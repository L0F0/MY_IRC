/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** lib
*/

#ifndef MY_IRC_H_
#define MY_IRC_H_

/***************************
          INCLUDES
 ***************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

/*****************************
          STRUTURES
 *****************************/

typedef struct s_client		t_client;
typedef struct s_clientOnServer	t_clientOnServer;
typedef struct s_server		t_server;
typedef struct s_chanel		t_chanel;

struct s_client
{
	int			fd;
	char			*name;
	char			*port_char;
	char			*addr;
	int			port;
	struct protoent		*pe;
	struct sockaddr_in	s_in;
};

struct s_chanel
{
	char	*name;
	int	id;
	t_chanel	*next;
};

struct s_clientOnServer
{
	int			client_fd;
	char			*name;
	int			value;
	int			id_chanel;
	struct sockaddr_in      s_in_client;
	socklen_t               s_in_size;
	t_clientOnServer	*next;
};

struct s_server
{
	int			fd;
	int			port;
	fd_set			readfd;
	struct timeval		tv;
	struct protoent		*pe;
	struct sockaddr_in	s_in;
	t_clientOnServer	*allClient;
	t_chanel		*chanel;
};

/****************************
         FUNCTIONS
 ****************************/

void		Usage();
void		parse_arg(char *str, int cs1, t_server *server);
void		Usage_client();
int		check_argv_for_client(char **av);
int		check_argv_for_server(char **av);
int		check_fd(int fd);
int		check_close(int fd);
int		check_bind(int fd, const struct sockaddr *sin, size_t sin2);
int		check_listen(int fd, int nb);
t_server	*init_server(t_server *server, char **av);
t_client	*init_client(t_client *client, char **av);
int		server(char **av);
int		load_server(int port, struct sockaddr_in s_in);
struct sockaddr_in	initial(struct sockaddr_in s_in, int port);
int		launch_client();
int		launch_server(char **av);
void		epur_str(char *str);
void		getnickname(char *str, t_server *server, int cs1);
int		handle_client(t_server *server);
void		printAllClient(t_server *server);
int		initTheServer(t_server *server, char **av);
int		initTheServerNext(t_server *server);
void		join_chanel(char *str, int cs1, t_server *server);
int		find_space(char *str);
int		getcommand(char *str);
char		*word_after_space(char *str);
void		user_function(char *str, int cs1, t_server *server);

/*************************
          MACROS
 *************************/

# define SUCCESS 0
# define FAIL 1
# define ERROR 84

#endif /* !MY_IRC_H_ */
