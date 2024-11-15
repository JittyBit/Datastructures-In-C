.PHONY: clean

build: main.o hashmap.o
	gcc -g -ggdb -w -Wall -Wextra -Werror -Wpedantic -o build main.o hashmap.o

main.o: main.c 
	gcc -g -ggdb -w -Wall -Wextra -Werror -Wpedantic -c main.c 

hashmap.o: hashmap.c 
	gcc -g -ggdb -w -Wall -Wextra -Werror -Wpedantic -c hashmap.c 

clean: 
	rm *.o 

