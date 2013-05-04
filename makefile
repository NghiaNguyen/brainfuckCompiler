CXX=g++
CXXFLAGS=-O3 -std=c++0x -pg -D_DEBUG -g -c -Wall

all: brainfuck

brainfuck: brainfuck.o
	g++ -o bf brainfuck.o && rm brainfuck.o

brainfuck.o: brainfuck.cpp
