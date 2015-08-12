solitaire:	main.o cards.o
	gcc -o solitaire main.o cards.o -Wall -pedantic -std=c99
main.o:	main.c
	gcc -o main.o -c main.c -Wall -pedantic -std=c99
cards.o:	cards.c
	gcc -o cards.o -c cards.c -Wall -pedantic -std=c99