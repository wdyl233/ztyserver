#include <stdlib.h>
#include <stdio.h>
#include "init_socket.h"

int main(int argc, char **argv)
{
	int listen_fd;
	int connect_fd;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	if (init_socket(&listen_fd, &server_addr) == -1) {
		perror("init_socket() error in ztyserver.c");
		exit(EXIT_FAILURE);
	}

}
