all: main.o boroughs.o
	rm boroughs.data
	gcc -o main main.c boroughs.c

main.o: main.c boroughs.h
	gcc -c main.c

boroughs.o: boroughs.c boroughs.h
	gcc -c boroughs.c

