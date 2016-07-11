#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>
#include "init_socket.h"
#include "epoll_module.h"

int main(int argc, char **argv)
{
    pid_t pid;

    int listen_fd;
    int connect_fd;
    int i;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    struct epoll_event ev;
    struct epoll_event events[MAXEPOLLSIZE];
    char buf[MAXLINE];
    int epoll_fd;

    if (init_socket(&listen_fd, &server_addr) == -1) {
        perror("init_socket() error in ztyserver.c");
        exit(EXIT_FAILURE);
    }

    if (set_limit() == -1) {
        perror("set_limit() error in ztyserver.c");
        exit(EXIT_FAILURE);
    }

    init_epoll(&listen_fd, &ev, &epoll_fd);
    epoll_loop(&listen_fd, &epoll_fd, &client_addr, events, &ev);
}

int set_limit()
{
    /* 设置每个进程允许打开的最大文件数 */
    struct rlimit rt;
    rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) {
        perror("setrlimit error");
        return -1;
    }
}
