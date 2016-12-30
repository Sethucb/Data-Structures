all: program7.o bst.o
	gcc -g -o program7 program7.c bst.c

run: all
	./program7

program7.o: program7.c
	gcc -g -c program7.c -o program7.o

bst.o: bst.c
	gcc -g -c bst.c -o bst.o

checkmem: run
	valgrind ./program7

clean: program7 program7.o bst.o
	rm -rf program7 program7.o bst.o
	
