.PHONY: clean

main: main.o vector.o
	gcc -o main main.o vector.o

main.o: main.c 
	gcc -c main.c 

vector.o: vector.c 
	gcc -c vector.c 

clean:
	rm *.o
