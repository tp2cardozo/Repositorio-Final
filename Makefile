CFLAGS= -Wall -Werror -pedantic -O2 -std=c89

CC=gcc

all:mp3explorer

mp3explorer: vector.o track.o mp3.o errors.o setup.o contexts.o mp3_processor.o main.o 
	$(CC) $(CFLAGS) -o mp3explorer main.o errors.o mp3_processor.o vector.o track.o setup.o contexts.o mp3.o
	
vector.o:vector.h vector.c types.h
	$(CC) $(CFLAGS) -o vector.o -c vector.c

track.o:track.h track.c types.h
	$(CC) $(CFLAGS) -o track.o -c track.c

mp3.o:mp3.c mp3.h types.h track.h
	$(CC) $(CFLAGS) -o mp3.o -c mp3.c

contexts.o:contexts.h contexts.c types.h
	$(CC) $(CFLAGS) -o contexts.o -c contexts.c

mp3_processor.o:mp3_processor.h mp3_processor.c vector.h track.h types.h errors.h
	$(CC) $(CFLAGS) -o mp3_processor.o -c mp3_processor.c

main.o:main.h main.c errors.h vector.h types.h setup.h
	$(CC) $(CFLAGS) -o main.o -c main.c

errors.o:errors.h errors.c types.h
	$(CC) $(CFLAGS) -o errors.o -c errors.c

setup.o:setup.h setup.c types.h
	$(CC) $(CFLAGS) -o setup.o -c setup.c

clean:
	rm *.o
