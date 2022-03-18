CC=gcc
LD_FLAGS=-lgmp


all: dir main

clean:
	rm -rf ./out

dir:
	mkdir -p ./out 

main: main.o
	${CC} ${LD_FLAGS} -o ./out/main ./out/main.o
main.o:
	${CC} -c -o ./out/main.o main.c
