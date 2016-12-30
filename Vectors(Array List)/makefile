all: program5.o vector.o
	gcc -g -o program5 program5.c vector.c

run: all
	./program5

program5.o: program5.c
	gcc -g -c program5.c -o program5.o

vector.o: vector.c
	gcc -g -c vector.c -o vector.o

checkmem: all
	valgrind ./program5

clean:
	rm -rf program5 program5.o vector.o
