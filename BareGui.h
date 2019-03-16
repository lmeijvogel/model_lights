#ifndef BARE_GUI_H
#define BARE_GUI_H

#include "Gui.h"

class BareGui : public Gui {
public:
  virtual void init();
  virtual void print(int position, char *line);
  virtual void finish();
};

#endif
