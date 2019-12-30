all: main.o
	gcc -o control main.c

main.o: main.c
	gcc -c main.c

run -c:
	./control -c

run -r:
	./control -r

run -v:
	./control -v
