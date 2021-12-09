all: main.o
	gcc -o p.out main.c

main.o: main.c
	gcc -c main.c

run:
	./p.out