CFLAGS= -Wall -Werror -pedantic -O2 -std=c89

cc=gcc

all:mp3explorer

mp3explorer: main.o errors.o mp3_processor.o vector.o track.o setup.o
	$(cc) $(CFLAGS) -o mp3explorer main.o errors.o mp3_processor.o vector.o track.o setup.o


main.o:main.h main.c errors.h vector.h types.h setup.h
	$(cc) $(CFLAGS) -o main.o -c main.c

errors.o:errors.h errors.c types.h
	$(cc) $(CFLAGS) -o errors.o -c errors.c

mp3_processor.o:mp3_processor.h mp3_processor.c vector.h track.h types.h errors.h
	$(cc) $(CFLAGS) -o mp3_processor.o -c mp3_processor.c

vector.o:vector.h vector.c types.h
	$(cc) $(CFLAGS) -o vector.o -c vector.c

track.o:track.h track.c types.h
	$(cc) $(CFLAGS) -o track.o -c track.c

setup.o:setup.h setup.c types.h
	$(cc) $(CFLAGS) -o setup.o -c setup.c

clean:
	rm *.o
