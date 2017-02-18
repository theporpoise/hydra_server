#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
**int socket(int domain, int type, int protocol);
**int	daemon(int nochdir, int noclose);
*/

int main()
{
	char				str[100];
	int					listenfd;
	int					commfd;
	struct sockaddr_in 	servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(22000);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 10);

	commfd = accept(listenfd, (struct sockaddr*) NULL, NULL);

	while (1)
	{
		bzero(str, 100);
		read(commfd, str, 100);
		printf("Echoing back - %s", str);
		if (strncmp(str, "ping", 4) == 0)
		{
			write(commfd, "pong\npong\n", 10);
		}
		else
		{
			write(commfd, str, strlen(str) + 1);
			write(commfd, str, strlen(str) + 1);
		}

	}
}
