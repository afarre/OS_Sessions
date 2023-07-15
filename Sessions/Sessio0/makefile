all:Sessio0


file.o: file.h file.c types.h
	gcc -c file.c -Wall -Wextra


main.o: main.c file.h
	gcc -c main.c -Wall -Wextra


Sessio0: file.o main.o
	gcc file.o main.o -o s0


clean:
	rm -f *.o Sessio0
