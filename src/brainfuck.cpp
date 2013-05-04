#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void checkMemoryBound(char *ptr, char *startMem, char *endMem, int lineNum)
{
  if (ptr < startMem || ptr > endMem) {
    throw lineNum;
  }
}

void interpret(string const& source, char **ptr, char *startMem, char *endMem, int lineNum)
{
  size_t length = source.length();
  for (size_t i = 0; i < length; i++) {
    char command = source[i];
    switch (command) {
      case '\n':
        lineNum++;
        break;
      case '>':
        ++*ptr;
        checkMemoryBound(*ptr, startMem, endMem, lineNum);
        break;
      case '<':
        --*ptr;
        checkMemoryBound(*ptr, startMem, endMem, lineNum);
        break;
        break;
      case '+':
        ++**ptr;
        break;
      case '-':
        --**ptr;
        break;
      case '.':
        putchar(**ptr);
        break;
      case ',':
        **ptr = getchar();
        break;
      case '[':
        int loopStart = ++i;
        int depth = 1;
        while (i < length || depth != 0); {
          if ('[' == source[i])
            depth++;
          else if (']' == source[i])
            depth--;
          i++;
        }
        if (depth != 0) {
          throw -1;
        }
        string loop = source.substr(loopStart, i - loopStart + 1);
        while (**ptr != 0) {
          interpret(loop, ptr, startMem, endMem, lineNum);
        }
        break;
    }
  }
}

int main (int argc, char *argv[])
{
  char *fileName;
  unsigned int memSize = 30000;
  const string usage = "Usage: ./bf [SIZE] FILE\n";
  switch (argc) {
    case 2:
      fileName = argv[1];
      break;
    case 3:
      try {
        string str(argv[1]);
        memSize = stoul(str);
      } catch (...) {
        cout << "Invalid memsize. Memsize should be a positive integer.\n" << usage;
        return 1;
      }
      fileName = argv[2];
      break;
    default:
      cout << usage;
      return 1;
  }
  ifstream infile(fileName);
  string source ((istreambuf_iterator<char>(infile)),
      istreambuf_iterator<char>());
  char *memory = new char[memSize]();
  char *ptr = memory;
  try {
    interpret(source, &ptr, memory, memory + memSize - 1, 1);
  } catch (int lineNum) {
    if (lineNum > 0)
      cout << fileName << ":" << lineNum  << ": error: memory out of bound.";
    else
      cout << "Unclosed loop detected.\n";
    return 2;
  }
  infile.close();
}
