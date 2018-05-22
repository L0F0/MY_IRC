##
## EPITECH PROJECT, 2018
## Philosopher
## File description:
## makefile
##

RM	=	rm -f

CC	=	gcc -g3

CFLAGS	=	-W -Wall -Werror -Wextra -I$(HEADER)

HEADER	=	./include

DIR	=	src

SRCS	=	$(DIR)/main.c		\
		$(DIR)/check_argv.c	\
		$(DIR)/init.c		\
		$(DIR)/check.c		\
	 	$(DIR)/launch_server.c  \
                $(DIR)/launch_client.c	\
		$(DIR)/epur_str.c	\
		$(DIR)/parse.c		\
		$(DIR)/command.c


OBJS	=	$(SRCS:.c=.o)


NAME	=	client
NAME2	=	server

all:	$(NAME) $(NAME2)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
	$(CC) $(OBJS) -o $(NAME2) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME) $(NAME2)

re:	all clean

.PHONY:	all clean fclean re
