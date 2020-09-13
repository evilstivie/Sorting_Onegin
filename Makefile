main.o: main.c
	gcc main.c -c -o main.o

file.o: file.c
	gcc file.c -c -o file.o

sort.o: sort.c
	gcc sort.c -c -o sort.o

onegin: main.o file.o sort.o
	gcc main.o file.o sort.o -o onegin

run: onegin
	make clear
	clear
	./onegin
	

clear:
	rm *.o
