all: programa limpa

programa: main.o interface.o interface.h
	gcc main.o interface.o -o programa -g

main.o: main.c interface.h interface.c
	gcc -c main.c
	
interface.o: interface.h interface.c
	gcc -c interface.c

limpa:
	rm *.o
