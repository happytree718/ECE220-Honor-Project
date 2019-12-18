CC=gcc
CFLAGS=-g -Wall

All: main.o io.o print.o
	$(CC) $(CFLAGS) main.o io.o print.o -o honor

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

print.o: print.c
	$(CC) $(CFLAGS) -c print.c

clean:
	rm -f main.o io.o print.o honor output_table.txt output_readable.txt
