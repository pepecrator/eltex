cli: cli.o serv.o
	gcc cli.o -o cli
	gcc serv.o -o serv

serv: serv.o
	gcc serv.o -o serv

cli.o: cli.c
	gcc -c cli.c

serv.o: serv.c
	gcc -c serv.c


