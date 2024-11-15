.PHONY: clean

build: main.o linked_list.o
	gcc -o build main.o linked_list.o

main.o: main.c 
	gcc -c main.c 

linked_list.o: linked_list.c 
	gcc -c linked_list.c

clean:
	rm *.o

