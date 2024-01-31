
all: strmod

strmod: mainpgm.o helper.o
	gcc -o strmod mainpgm.o helper.o -lm
mainpgm.o: mainpgm.c helper.o
	gcc -c mainpgm.c
helper.o: helper.c helper.h
	gcc -c helper.c

clean:
	rm -f *.o strmod



