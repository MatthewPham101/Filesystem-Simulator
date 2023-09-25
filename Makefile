prog: FileSystem.o 
	gcc FileSystem.o -o output
FileSystem.o: Filesystem.c 
	gcc -c -g -Wall -std=c99 Filesystem.c
clean:
	-rm *.o 
run: 
	@./output
