EXEC =  tp1
CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -g
BIN = $(filter-out $(EXEC).c, $(wildcard *.c))
BINFILES = $(BIN:.c=.o)

all: main

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
	
main: $(BINFILES)  $(EXEC).c
	$(CC) $(CFLAGS) $(BINFILES) $(EXEC).c -o $(EXEC)

clean:
	rm -f $(wildcard *.o) $(EXEC)

test: $(EXEC)
	bash test/correr-pruebas.sh $(EXEC)

.PHONY: clean main