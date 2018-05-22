#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int s;
	int cs;
	struct sockaddr_in sin;
	struct sockaddr_in client_sin;
	int client_sin_len;
	int port;
	s = socket(PF_INET, SOCK_STREAM, 0);
	port = atoi(argv[1]);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	bind(s, (struct sockaddr*)&sin, sizeof(sin));
	listen(s, 42);
	client_sin_len = sizeof(client_sin);
	while (1)
	{
		fd_set readf;
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		FD_ZERO(&readf);
		FD_SET(s, &readf);
		if (select(s + 1, &readf, NULL, NULL, &tv) == -1)
			perror("select");
		if (FD_ISSET(s, &readf))
		{
			printf("New client\n");
			cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
			close(cs);
		}
		else
		{
			printf("waiting...\n");
		}
	}
	close(s);
	return (0);
}
