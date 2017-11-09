sig: main.o
	gcc -o sig main.o
	make clean

main.o: main.c
	gcc -c main.c

clean:
	rm *.o

run:
	./sig
