all: control.o write.o
	gcc -o control control.c
	gcc -o write write.c

control.o: control.c
	gcc -c control.c

write.o: write.c
	gcc -c write.c
