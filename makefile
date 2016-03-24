simulation:	proj2.o queue.o stats.o 
	gcc -Wall proj2.o queue.o stats.o -lm -o simulation
proj2.o:	proj2.c
queue.o:	queue.c
stats.o:	stats.c

test: test1
test1:
	./simulation
