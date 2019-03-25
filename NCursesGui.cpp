#include <ncurses.h>
#include <stdlib.h>

#include "NCursesGui.h"
#include "src/GuiLight.h"

typedef GuiLight* GuiLightPtr;

const int HEADER_SIZE = 10;

NCursesGui::NCursesGui(StateMachine *stateMachine,
                       WheelStateMachine *wheelStateMachine,
                       CircularActivator *circularActivator,
                       LightPtr *lights,
                       int numberOfLights,
                       GuiLight *statusOffLight,
                       GuiLight *statusGradualLight,
                       GuiLight *statusOnLight) {
  this->stateMachine = stateMachine;
  this->wheelStateMachine = wheelStateMachine;
  this->circularActivator = circularActivator;
  this->lights = lights;
  this->numberOfLights = numberOfLights;
  this->statusOffLight = statusOffLight;
  this->statusGradualLight = statusGradualLight;
  this->statusOnLight = statusOnLight;
}
void NCursesGui::init() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  refresh();
}

void NCursesGui::printIntro() {
  this->print(0, (char *)"q: Quit\n");
  this->print(0, (char *)"z: Turn off\n");
  this->print(0, (char *)"x: Gradual\n");
  this->print(0, (char *)"c: Turn on\n");
  this->print(0, (char *)"\n");
  this->print(0, (char *)"<space>: toggle cycling/speed mode\n");
  this->print(0, (char *)"a: Cycle -2\n");
  this->print(0, (char *)"s: Cycle -1\n");
  this->print(0, (char *)"d: Cycle 1\n");
  this->print(0, (char *)"f: Cycle 2\n");

  refresh();
}

void NCursesGui::update() {
    this->printState();
    this->printLights();
    this->printStatusLeds();

    refresh();

}

void NCursesGui::finish() {
  endwin();
}

void NCursesGui::printState() {
  State state = this->stateMachine->getState();

  char description[60];

  switch (state) {
  case StateOff:
    sprintf(description, "%-59s", "StateOff");
    break;
  case StateTurningOn:
    sprintf(description, "%-59s", "StateTurningOn");
    break;
  case StateAnimating:
    sprintf(description, "%-59s", "StateAnimating");
    break;
  case StateOn:
    sprintf(description, "%-59s", "StateOn");
    break;
  case StateTurningOff:
    sprintf(description, "%-59s", "StateTurningOff");
    break;
  }

  this->print(HEADER_SIZE + 2, description);

  switch (this->wheelStateMachine->getState()) {
    case StateCycling:
        sprintf(description,
                "%s: %d %d",
                "StateCycling",
                circularActivator->getCurrentLightIndex(),
                circularActivator->getIsActivating());
        break;
    case StateSpeed:
        sprintf(description,
                "%s: % 2d -> %.2f  ",
                "StateSpeed",
                wheelStateMachine->getSpeedRotation(),
                wheelStateMachine->getDelayFactor()
                );
        break;
  }

  this->print(HEADER_SIZE + 4, description);

  refresh();
}

void NCursesGui::printLights() {
  char *line = (char *)malloc(this->numberOfLights * 2 + 2);

  for (int i = 0 ; i < this->numberOfLights ; i++ ) {
    GuiLightPtr pLight = (GuiLightPtr)lights[i];

    line[2*i] = pLight->getState() ? '*' : '.';
    line[2*i+1] = ' ';
  }
  line[this->numberOfLights * 2 - 2] = '\n';
  line[this->numberOfLights * 2 - 1] = 0;

  this->print(HEADER_SIZE + 6, line);

  free(line);
}

void NCursesGui::addLightToBuffer(GuiLight *pLight, int position, char *output) {
    output[2*position] = pLight->getState() ? '*' : '.';
    output[2*position+1] = ' ';
}

void NCursesGui::printStatusLeds() {
  char line[3 * 2 + 2];

this->addLightToBuffer((GuiLightPtr)statusOffLight, 0, line);
this->addLightToBuffer((GuiLightPtr)statusGradualLight, 1, line);
this->addLightToBuffer((GuiLightPtr)statusOnLight, 2, line);

  this->print(HEADER_SIZE + 8, line);
}

void NCursesGui::print(int position, char *line) {
  if (position == 0) {
    printw(line);
  } else {
    mvprintw(position, 0, line);
  }
}
