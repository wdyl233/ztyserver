#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "epoll_module.h"

/** 初始化epoll并注册listen_fd **/
int init_epoll(int *listen_fd, struct epoll_event *ev, int *epoll_fd)
{
    *epoll_fd = epoll_create(MAXEPOLLSIZE);
    ev->events = EPOLLIN | EPOLLET;
    ev->data.fd = *listen_fd;

    if (epoll_ctl(*epoll_fd, EPOLL_CTL_ADD, *listen_fd, ev) < 0) {
        fprintf(stderr, "epoll set insertion error: fd=%d\n",
                listen_fd);
        return -1;
    }
}

int epoll_loop(int *listen_fd, int *epoll_fd, struct sockaddr_in *client_addr,
               struct epoll_event *events, struct epoll_event *ev)
{
    int nfds, n, confd, send_bytes, read_bytes;
    socklen_t socklen = sizeof(struct sockaddr_in);

    char recv_buf[RECV_BUFFER_SIZE + 1];
    unsigned char send_buf[SEND_BUFFER_SIZE + 1];

    for (;;) {
        nfds = epoll_wait(*epoll_fd, events, MAXEPOLLSIZE, -1);

        if (nfds == -1) {
            printf("epoll_wait() error in epoll_module.c");
            exit(EXIT_FAILURE);
        }

        for (n = 0; n < nfds; ++n) {

            if (events[n].data.fd == *listen_fd) {
                confd =
                    accept(*listen_fd,
                           (struct sockaddr *)client_addr,
                           &socklen);
                ev->data.fd = confd;
                ev->events = EPOLLIN | EPOLLET;
                epoll_ctl(*epoll_fd, EPOLL_CTL_ADD, confd, ev);
                printf("con_fd:=>%d\n",confd);
            }

            else {
                memset(recv_buf, '\0', sizeof(recv_buf));
                if (read_bytes =
                        recv(events[n].data.fd, recv_buf,
                             RECV_BUFFER_SIZE, 0) == 0) {
                    break;
                    //  return 0;
                }

                else {

                    printf("out_fd:=>%d\n",events[n].data.fd);
                    get_send_buf(recv_buf, send_buf,
                                 &send_bytes);

                    int i;
                    for(i=0; i<10; i++) {
                        int send_str=send(events[n].data.fd, send_buf,
                                          send_bytes, 0);
                        printf("send_str%d\n",send_str);
                    }
					
                    shutdown(events[n].data.fd, SHUT_RDWR);
                    printf("*******\n");

                }
            }
        }
    }
}
