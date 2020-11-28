bc: main.o Number.o Number.h trigo.c trigo.h bc.o bc.h stack.o stack.h
	gcc -o bc main.o Number.o Number.h trigo.c trigo.h bc.o bc.h stack.o stack.h

main.o: main.c
	gcc -c main.c -o main.o
bc.o: bc.c
	gcc -c bc.c -o bc.o
Number.o: Number.c
	gcc -c Number.c -o Number.o
stack.o: stack.c
	gcc -c stack.c -o stack.o
clean: 
	rm -f *.o -f *.h.gch