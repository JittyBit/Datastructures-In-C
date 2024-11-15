.PHONY: clean

build: main.o vector.o
	gcc -o build main.o vector.o

main.o: main.c 
	gcc -c main.c 

vector.o: vector.c 
	gcc -c vector.c 

clean:
	rm *.o
