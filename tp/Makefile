all:	app-hw1

app-hw1:	main.o initMatrix.o displayMatrix.o mul.o thread.o
	gcc main.o initMatrix.o displayMatrix.o mul.o thread.o -o mmm -lpthread

main.o:	main.c
	gcc -c main.c -o main.o 

initMatrix.o:	initMatrix.c
	gcc -c initMatrix.c -o initMatrix.o
	
displayMatrix.o:	displayMatrix.c
	gcc -c displayMatrix.c -o displayMatrix.o	

mul.o:	mul.c
	gcc -c mul.c -o mul.o
	
thread.o: thread.c
	gcc -c thread.c -o thread.o

clean:
	rm -fr app-hw1 *.o
