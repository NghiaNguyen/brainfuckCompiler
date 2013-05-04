CXX=g++
CXXFLAGS=-O3 -std=c++0x -pg -D_DEBUG -g -c -Wall

SRCDIR   = src
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(SRCDIR)/%.o)

brainfuck: $(OBJECTS)
	g++ -o bf $(OBJECTS) && rm $(OBJECTS)

$(OBJECTS): $(SOURCES)
