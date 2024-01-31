all: main
type ?= linkedlist

ifeq ($(type),array)
main: driver.o stackarr.o
	gcc -o main driver.o stackarr.o
driver.o: driver.c
	gcc -c driver.c
stackarr.o: stackarr.c
	gcc -c stackarr.c
else
main: driver.o stackll.o
	gcc -o main driver.o stackll.o
driver.o: driver.c stackll.o
	gcc -c driver.c
stackll.o: stackll.c
	gcc -c stackll.c
endif

clean:
	rm -f *.o main
