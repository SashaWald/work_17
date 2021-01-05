all: client.c server.c 
	gcc -o client.o client.c
	gcc -o server.o server.c

run: 
	./client.o & ./server.o

clean:
	rm *.out