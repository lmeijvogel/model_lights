#include <ncurses.h>
#include <string.h>

#include "BareGui.h"

void BareGui::init() {
}

void BareGui::print(int, char *line) {
  int lineSize = strlen(line);

  char *lineWithNewLine = new char[lineSize+1];

  strcpy(lineWithNewLine, line);
  lineWithNewLine[lineSize] = '\n';

  printf("%s", lineWithNewLine);

  delete lineWithNewLine;
}

void BareGui::finish() {
}
