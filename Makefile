CC = clang
CFLAGS = -g -Wall

all: server

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

server: server.o threadpool.o http.o error.o
	$(CC) $(CFLAGS)	$^ -o $@ -lpthread

clean:
	rm -f *.o server