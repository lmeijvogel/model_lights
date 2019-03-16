#include <ncurses.h>

#include "NCursesGui.h"

void NCursesGui::init() {
  initscr();
}

void NCursesGui::print(int position, char *line) {
  if (position == 0) {
    printw(line);
  } else {
    mvprintw(position, 0, line);
  }
}

void NCursesGui::finish() {
  endwin();
}
