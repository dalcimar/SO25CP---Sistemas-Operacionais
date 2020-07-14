#A Simple Ilustrative Makefile for soshell#
CC=gcc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o execute.o parse.o

all: soshell

main.o: shell.h	main.c
	$(CC) $(FLAGS) main.c
execute.o: shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o: shell.h parse.c
	$(CC) $(FLAGS) parse.c
soshell: $(OBS)
	$(CC) -o soshell $(OBS) $(LIBS)
clean limpar:
	rm -f *.o

