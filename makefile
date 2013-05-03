CXX=g++

all: brainfuck

brainfuck: brainfuck.o
	g++ -o bf brainfuck.o && rm brainfuck.o

brainfuck.o: brainfuck.cpp
