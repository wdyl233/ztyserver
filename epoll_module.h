/*
* file:epoll_init.h
*/

#ifndef EPOLL_MODULE_H
#define EPOLL_MODULE_H

#include <sys/epoll.h>
#include <netinet/in.h>

#define MAXEPOLLSIZE   10000
#define MAXLINE        1024000

#define RECV_BUFFER_SIZE  102400	/* 1KB of receive buffer */
#define SEND_BUFFER_SIZE  1024000	/* 1MB of send buffer */
#define URI_SIZE          128	/* length of uri request from client browse */

/* epoll_event用户自定义struct */

struct ep_data {
	char recv_buf[RECV_BUFFER_SIZE + 1];
	int fd;
};

/* epoll初始化 */
int init_epoll(int *listen_fd, struct epoll_event *ev, int *epoll_fd);

/* epoll循环(参数过多，建议用结构体代替) */
int epoll_loop(int *listen_fd, int *epoll_fd, struct sockaddr_in *client_addr,
	       struct epoll_event *events, struct epoll_event *ev);

#endif
