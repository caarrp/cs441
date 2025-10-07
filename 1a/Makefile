CC = gcc
CFLAGS = -Wall -g

image: 1_a.o
	$(CC) $(CFLAGS) -o image 1_a.o

1_a.o: 1_a.c
	$(CC) $(CFLAGS) -c 1_a.c

.PHONY: run
run: 
	./image
	display 1a.pnm

.PHONY: clean
clean:
	rm -f image *.o 1a.pnm
