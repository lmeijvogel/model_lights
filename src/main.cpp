#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <ncurses.h>

#include "StateMachine.hpp"
#include "LightController.hpp"
#include "Light.hpp"
#include "GuiLight.hpp"

const int NUMBER_OF_LIGHTS = 10;

const int GRADUAL_TRANSITION_PERIOD_MS = 6*1000;
typedef GuiLight* GuiLightPtr;

LightPtr *createLights();

void print_intro();

void print_state(StateMachine &stateMachine);
void print_lights(LightPtr *lights);

void handle_input(int ch, StateMachine &stateMachine, int elapsedTimeMs);

void cleanupAndExit() {
  endwin();

  exit(1);
}

void sigIntReceived(int s) {
  cleanupAndExit();
}

int main() {
  LightPtr *lights = createLights();

  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = sigIntReceived;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  LightController lightController(lights, NUMBER_OF_LIGHTS);

  StateMachine stateMachine(&lightController);

  initscr();

  print_intro();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  refresh();

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

  while (true) {
    usleep(200000);

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    int elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

    stateMachine.clockTick(elapsedTimeMs);
    int ch = getch();

    if (ch == 'q') {
      delete[] lights;
      cleanupAndExit();
    } else if (ch != ERR) {
      handle_input(ch, stateMachine, elapsedTimeMs);
    }
    print_state(stateMachine);
    print_lights(lights);

    refresh();
  }
}

LightPtr *createLights() {
  LightPtr *lights = new LightPtr[NUMBER_OF_LIGHTS];


  for (int i = 0 ; i < NUMBER_OF_LIGHTS ; i++) {
    GuiLight *light = new GuiLight;
    lights[i] = light;
  }

  return lights;
}

void print_intro() {
  printw("q: Quit\n");
  printw("z: Turn off\n");
  printw("x: Gradual\n");
  printw("c: Turn on\n");
  refresh();
}

void handle_input(int ch, StateMachine &stateMachine, int elapsedTimeMs) {
  switch(ch) {
  case 'z':
    stateMachine.switchOff();
    break;
  case 'x':
    stateMachine.switchGradual(elapsedTimeMs + GRADUAL_TRANSITION_PERIOD_MS);
    break;
  case 'c':
    stateMachine.switchOn();
    break;
  }
}

void print_state(StateMachine &stateMachine) {
  State state = stateMachine.getState();

  switch (state) {
  case StateOff:
    mvprintw(6, 0, "StateOff        ");
    break;
  case StateTurningOn:
    mvprintw(6, 0, "StateTurningOn  ");
    break;
  case StateAnimating:
    mvprintw(6, 0, "StateAnimating  ");
    break;
  case StateOn:
    mvprintw(6, 0, "StateOn        ");
    break;
  case StateTurningOff:
    mvprintw(6, 0, "StateTurningOff");
    break;
  }

  refresh();
}

void print_lights(LightPtr *lights) {
  for (int i = 0 ; i < NUMBER_OF_LIGHTS ; i++ ) {
    GuiLightPtr pLight = (GuiLightPtr)lights[i];

    int xPos = i * 2;
    const char *lightDisp = pLight->getState() ? "*" : ".";

    mvprintw(10, 10+xPos, "%s", lightDisp);
  }
}
