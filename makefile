bc: main.o Number.o Number.h
	gcc -o bc main.o Number.o Number.h

main.o: main.c
	gcc -c main.c -o main.o

Number.o: Number.c
	gcc -c Number.c -o Number.o

clean: 
	rm -f *.o -f *.h.gch