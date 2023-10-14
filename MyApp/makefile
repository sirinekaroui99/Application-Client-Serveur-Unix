client.o: client.c
	gcc client.c -o client
server.o: server.c
	gcc server.c -o server
client_fifo.o: client_fifo.c
	gcc client_fifo.c -o client_fifo
server_fifo.o:server_fifo.c
	gcc server_fifo.c -o server_fifo
MyApp.o: myapp.c
	gcc -o MyApp myapp.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
