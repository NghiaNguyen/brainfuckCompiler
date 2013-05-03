#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int MEMORY_SIZE = 30000;

using namespace std;

void checkMemoryBound(char *ptr, char* startMem, int lineNum) {
  if (ptr < startMem || ptr >= MEMORY_SIZE + startMem) {
    throw lineNum;
  }
}

void interpret(string const& source, char **ptr, char* startMem, int lineNum) {
  int length = source.length();
  for (int i = 0; i < length; i++) {
    char command = source[i];
    switch (command) {
      case '\n':
        lineNum++;
        break;
      case '>':
        ++*ptr;
        checkMemoryBound(*ptr, startMem, lineNum);
        break;
      case '<':
        --*ptr;
        checkMemoryBound(*ptr, startMem, lineNum);
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
        i++;
        stringstream ss;
        while (source[i] != ']') {
          ss << source[i];
          i++;
        }
        string loopSource = ss.str();
        while (**ptr != 0) {
          interpret(loopSource, ptr, startMem, lineNum);
        }
        break;
    }
  }
}

int main (int argc, char * argv[])
{
  char* fileName;
  switch (argc) {
    case 2:
      fileName = argv[1];
      break;
    case 3:
      break;
    default:
      cout << "Usage: ./bf [memory size] <file name>\n";
      return 1;
  }
  ifstream infile(fileName);
  string source ((istreambuf_iterator<char>(infile)),
                       istreambuf_iterator<char>());
  char *memory = new char[MEMORY_SIZE];
  char *ptr = memory;
  try {
    interpret(source, &ptr, memory, 1);
  } catch (int lineNum) {
    cout << fileName << ":" << lineNum  << ": error: memory out of bound.";
    return 1;
  }
  infile.close();
}
