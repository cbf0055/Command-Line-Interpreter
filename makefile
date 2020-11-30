output: main.o
	gcc main.o -o output
major1.o: main.c
	gcc -c -Wall main.c
clean:
	rm *.o output