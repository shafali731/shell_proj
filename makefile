all: commands.o shell.o
	gcc commands.o shell.o

forkin.o: commands.c commands.h
	gcc -c commands.c

shell.o: shell.c commands.h
	gcc -c shell.c

run:
	./a.out

clean: shell.o
	rm *.o a.out
