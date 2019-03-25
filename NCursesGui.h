#ifndef NCURSES_GUI_H
#define NCURSES_GUI_H

#include "Gui.h"
#include "src/StateMachine.h"
#include "src/WheelStateMachine.h"
#include "src/CircularActivator.h"
#include "src/GuiLight.h"
#include "src/Light.h"

typedef Light* LightPtr;

class NCursesGui : public Gui {
public:
  NCursesGui(StateMachine *stateMachine,
             WheelStateMachine *wheelStateMachine,
             CircularActivator *circularActivator,
             LightPtr *lights,
             int numberOfLights,
             GuiLight *statusOffLight,
             GuiLight *statusGradualLight,
             GuiLight *statusOnLight);
  virtual void init();
  virtual void printIntro();
  virtual void update();
  virtual void finish();
private:
  StateMachine *stateMachine;
  WheelStateMachine *wheelStateMachine;
  CircularActivator *circularActivator;
  LightPtr *lights;
  int numberOfLights;
  GuiLight *statusOffLight;
  GuiLight *statusGradualLight;
  GuiLight *statusOnLight;

  void printState();
  void printLights();
  void printStatusLeds();

  virtual void print(int position, char *line);

  void addLightToBuffer(GuiLight *pLight, int position, char *output);

};

#endif
