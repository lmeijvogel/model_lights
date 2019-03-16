#ifndef GUI_H
#define GUI_H

class Gui {
public:
  virtual void init() = 0;
  virtual void print(int position, char *line) = 0;
  virtual void finish() = 0;
};

#endif
