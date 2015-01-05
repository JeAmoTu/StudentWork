main:main.o add.o sub.o
	gcc -Wall -O3 -o main main.o add.o sub.o
main.o:main.c
	gcc -Wall -O3 -c main.c
add.o:add.c
	gcc -Wall -O3 -c add.c
sub.o:sub.c
	gcc -Wall -O3 -c sub.c
.PHONY:clean install all
clean:
	rm -f main.o add.o sub.o
install:
	mv main bin
all:clean install
