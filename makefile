all: rubiks

rubiks: main.o rubiks.o print.o movements.o file.o array.o menu.o
	gcc main.o rubiks.o print.o movements.o file.o array.o menu.o -g -o rubiks

main.o: main.c rubiks.h
	gcc main.c -c -g -Wall -Werror -o main.o

rubiks.o: rubiks.c rubiks.h color.h
	gcc rubiks.c -c -g -Wall -Werror -o rubiks.o

print.o: print.c rubiks.h color.h
	gcc print.c -c -g -Wall -Werror -o print.o

movements.o: movements.c rubiks.h
	gcc movements.c -c -g -Wall -Werror -o movements.o

file.o: file.c rubiks.h
	gcc file.c -c -g -Wall -Werror -o file.o

array.o: array.c rubiks.h
	gcc array.c -c -g -Wall -Werror -o array.o

menu.o: menu.c rubiks.h
	gcc menu.c -c -g -Wall -Werror -o menu.o

clean:
	rm -f save1.txt save2.txt save3.txt main.o rubiks.o print.o movements.o file.o array.o menu.o rubiks
