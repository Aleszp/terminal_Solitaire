solitaire:	main.o game.o prepare.o
	gcc -o solitaire main.o game.o prepare.o -Wall -pedantic -std=c99
main.o:	main.c
	gcc -o main.o -c main.c -Wall -pedantic -std=c99
game.o:	game.c
	gcc -o game.o -c game.c -Wall -pedantic -std=c99
prepare.o:	prepare.c
	gcc -o prepare.o -c prepare.c -Wall -pedantic -std=c99	