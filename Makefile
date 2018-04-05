CC = g++
FLAGS = -g -Wall
MAIN = simulo 

$(MAIN):  simulo.o mem.o loader.o

	$(CC) $(FLAGS) -o simulo simulo.o mem.o loader.o

simulo.o: mem.h loader.h allstdlib.h

mem.o: mem.h allstdlib.h

loader.o: loader.h mem.h

clean:
	rm -rf *.o $(MAIN)
