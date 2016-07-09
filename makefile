install:init_socket.o ztyserver.o
	gcc -g -o ztyserver init_socket.o ztyserver.o
	
ztyserver.o:ztyserver.c
	gcc -g -c ztyserver.c
	
init_socket.o:init_socket.c
	gcc -g -c init_socket.c
	
clean:
	rm -rf ztyserver
	rm -rf *.o