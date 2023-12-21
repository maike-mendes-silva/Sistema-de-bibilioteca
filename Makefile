all: LibraSys.exe

LibraSys.exe: main.o
	gcc -o LibraSys.exe main.o

main.o: .\src\main.c .\include\user.h .\include\book.h
	gcc -c .\src\main.c -I.\include -o main.o

clean:
	del *.o LibraSys.exe
