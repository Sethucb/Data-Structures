all: program6.o list.o
	gcc -g -o program6 program6.c list.c

program6.o: program6.c
	gcc -g -c program6.c -o program6.o

list.o: list.c
	gcc -g -c list.c -o list.o

run: all
	./program6

checkmem: all
	valgrind ./program6

clean:
	rm -rf program6 program6.o list.o
