binary: l24.o libcalk.a
	gcc -o binary l24.o -L. -lcalk

l24.o: l24.c
	gcc -c l24.c

libcalk.a: plus.o minus.o del.o mul.o
	ar cr libcalk.a plus.o minus.o del.o mul.o

plus.o: plus.c
	gcc -c plus.c

minus.o: minus.c
	gcc -c minus.c

del.o: del.c
	gcc -c del.c

mul.o: mul.c
	gcc -c mul.c

clean: 
	rm -f *.o *.a binary
