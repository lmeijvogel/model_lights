#ifndef NCURSES_GUI_H
#define NCURSES_GUI_H

#include "Gui.h"

class NCursesGui : public Gui {
public:
  virtual void init();
  virtual void print(int position, char *line);
  virtual void finish();
};

#endif
