#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <ncurses.h>
#include <random>

#include "StateMachine.hpp"
#include "LightCollectionController.hpp"
#include "LightController.hpp"
#include "Light.hpp"
#include "GuiLight.hpp"

const int NUMBER_OF_LIGHTS = 10;

const int GRADUAL_TRANSITION_PERIOD_MS = 6*1000;
typedef LightController* LightControllerPtr;
typedef GuiLight* GuiLightPtr;

GuiLightPtr *createLights();
LightControllerPtr *createLightControllers(GuiLightPtr *lights, int count, std::default_random_engine generator);

void print_intro();

void print_state(StateMachine &stateMachine);
void print_lights(GuiLightPtr *lights);

void handle_input(int ch, StateMachine &stateMachine, int elapsedTimeMs);
int seconds_since_epoch();

void cleanupAndExit() {
  endwin();

  exit(1);
}

void sigIntReceived(int s) {
  cleanupAndExit();
}

int main() {
  auto startTime = std::chrono::system_clock::now();

  GuiLightPtr *lights = createLights();

  // Use a single generator to make sure that all lights get *different* random timings.
  std::default_random_engine generator;

  // Good enough for animating model house lights :D
  generator.seed(seconds_since_epoch());

  LightControllerPtr *lightControllers = createLightControllers(lights, NUMBER_OF_LIGHTS, generator);

  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = sigIntReceived;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  LightCollectionController lightCollectionController(lightControllers, NUMBER_OF_LIGHTS);

  StateMachine stateMachine(&lightCollectionController);

  initscr();

  print_intro();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  refresh();

  while (true) {
    usleep(200000);

    auto now = std::chrono::system_clock::now();

    int elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

    stateMachine.clockTick(elapsedTimeMs);

    lightCollectionController.clockTick(elapsedTimeMs);

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

GuiLightPtr *createLights() {
  GuiLightPtr *lights = new GuiLightPtr[NUMBER_OF_LIGHTS];

  for (int i = 0 ; i < NUMBER_OF_LIGHTS ; i++) {
    GuiLight *light = new GuiLight;
    lights[i] = light;
  }

  return lights;
}

LightControllerPtr *createLightControllers(GuiLightPtr *lights, int count, std::default_random_engine generator) {
  LightControllerPtr *lightControllers = new LightControllerPtr[count];

  for (int i = 0 ; i < count ; i++) {
    LightController *lightController = new LightController(lights[i], &generator);
    lightControllers[i] = lightController;
  }

  return lightControllers;
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

void print_lights(GuiLightPtr *lights) {
  for (int i = 0 ; i < NUMBER_OF_LIGHTS ; i++ ) {
    GuiLightPtr pLight = (GuiLightPtr)lights[i];

    int xPos = i * 2;
    const char *lightDisp = pLight->getState() ? "*" : ".";

    mvprintw(10, 10+xPos, "%s", lightDisp);
  }
}

int seconds_since_epoch() {
  auto start = std::chrono::system_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
}
