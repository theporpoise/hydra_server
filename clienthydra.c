#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
**int socket(int domain, int type, int protocol);
**int	daemon(int nochdir, int noclose);
*/

int main(int ac, char **av)
{
	int					sockfd;
	int					n;
	char				sendline[100];
	char				recvline[100];
	struct sockaddr_in	servaddr;


	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(22000);

	inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	while (1)
	{
		bzero(sendline, 100);
		bzero(recvline, 100);
		fgets(sendline, 100, stdin);

		write(sockfd, sendline, strlen(sendline) + 1);
		read(sockfd, recvline, 100);
		printf("%s", recvline);
	}
}
