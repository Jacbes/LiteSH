all: DyLib libstrings.so
	
DyLib: main.c
	gcc -Wall -o DyLib main.c -ldl

libstrings.so: strings.o
	gcc -shared -o libstrings.so strings.o

strings.o: strings.c
	gcc -fPIC -c strings.c

clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf DyLib