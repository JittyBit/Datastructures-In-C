.PHONY: clean

build: main.o hashmap.o
	gcc -o build main.o hashmap.o

main.o: main.c 
	gcc -c main.c 

hashmap.o: hashmap.c 
	gcc -c hashmap.c 

clean: 
	rm *.o 

