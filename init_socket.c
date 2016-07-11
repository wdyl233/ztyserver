/**
* file:init_socket.c
*/
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "init_socket.h"

int setnonblocking(int sockfd)
{
	if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) ==
	    -1) {
		return -1;
	}
	return 0;
}

int init_socket(int *listen_fd, struct sockaddr_in *server_addr)
{
	if ((*listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error. in init_socket.c");
		return -1;
	}

    /** set reuse the port on server machine **/
	int opt = SO_REUSEADDR;

	if (setsockopt
	    (*listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt,
	     sizeof(opt))
	    == -1) {
		perror("setsockopt() error. in init_socket.c");
		return -1;
	}

	int optlen = sizeof(int);
	int optsdbuf = SOCKET_SENDBF;

	if (setsockopt
	    (*listen_fd, SOL_SOCKET, SO_SNDBUF, &optsdbuf, sizeof(int)) == -1) {
		perror("setsockopt() error. in init_socket.c");
		return -1;
	}
	getsockopt(*listen_fd, SOL_SOCKET, SO_SNDBUF, &optsdbuf, &optlen);

	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(PORT);
	server_addr->sin_addr.s_addr = htonl(INADDR_ANY);

	if (setnonblocking(*listen_fd) < 0) {
		perror("setnonblock error");
	}

	if (bind
	    (*listen_fd, (struct sockaddr *)server_addr,
	     sizeof(struct sockaddr_in)) == -1) {
		perror("bind() error. in init_socket.c");
		return -1;
	}

	if (listen(*listen_fd, BACKLOG) == -1) {
		perror("listen() error. in init_socket.c");
		return -1;
	}

	return 0;
}
