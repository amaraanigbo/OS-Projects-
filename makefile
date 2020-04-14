SOURCES = myshell.c
OBJECTS = myshell.o
HEADERS = myshell.h
CC = gcc
CFLAGS = -g -Wall

myshell: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o myshell

clean:
	rm -fR *o myshell
