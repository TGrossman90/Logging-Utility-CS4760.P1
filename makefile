all: p1 clear readme

p1: log.o main.o
	gcc -o p1 log.o main.o
	
main.o: main.c main.h
	gcc -c main.c

log.o: log.c log.h
	gcc -c log.c
	
clean: remove clear success

remove:
	rm *.o p1

clear: 
	clear
	
success: 
	$(info SUCCESS)
	
readme:
	cat README
