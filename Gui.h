#ifndef GUI_H
#define GUI_H

class Gui {
public:
  virtual void init() = 0;
  virtual void update() = 0;
  virtual void printIntro() = 0;
  virtual void finish() = 0;
};

#endif
