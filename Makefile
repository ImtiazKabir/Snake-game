all:
	g++ -c -Wall -Wextra main.cpp
sfml:
	g++ main.o -o game -lsfml-graphics -lsfml-system -lsfml-window

