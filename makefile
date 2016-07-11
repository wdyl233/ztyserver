install:init_socket.o ztyserver.o epoll_module.o http_protocol.o get_time.o
	gcc -Wall -g -o ztyserver init_socket.o ztyserver.o epoll_module.o http_protocol.o get_time.o
	
ztyserver.o:ztyserver.c
	gcc -g -c ztyserver.c
	
init_socket.o:init_socket.c
	gcc -g -c init_socket.c

epoll_module.o:epoll_module.c
	gcc -g -c epoll_module.c

http_protocol.o:http_protocol.c
	gcc -g -c http_protocol.c

get_time.o:get_time.c
	gcc -g -c get_time.c
	
clean:
	rm -rf ztyserver
	rm -rf *.o