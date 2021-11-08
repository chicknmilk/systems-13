all: main.o boroughs.o
	gcc -o main main.c boroughs.c

main.o: main.c boroughs.h
	gcc -c main.c

boroughs.o: boroughs.c boroughs.h
	gcc -c boroughs.c

clean:
	git add .
	git commit -m "Update"
	git push