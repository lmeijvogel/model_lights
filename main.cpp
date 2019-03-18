#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <ncurses.h>
#include <string.h>

#include "src/StateMachine.h"
#include "src/WheelStateMachine.h"
#include "src/LightCollectionController.h"
#include "src/LightController.h"
#include "src/Light.h"
#include "src/GuiLight.h"
#include "src/CircularActivator.h"
#include "Gui.h"
#include "NCursesGui.h"
#include "BareGui.h"

const int NUMBER_OF_LIGHTS = 50;
const int GRADUAL_TRANSITION_PERIOD_MS = 60*1000;

const int ON_TIME_DURATION = 120*1000;
const int OFF_TIME_DURATION = 12*1000;

const int headerSize = 10;

typedef LightController* LightControllerPtr;
typedef GuiLight* GuiLightPtr;

GuiLightPtr *createLights();
LightControllerPtr *createLightControllers(GuiLightPtr *lights, int count, RandomGenerator *randomGenerator);

CircularActivator *circularActivator;

Gui *gui;

void print_intro();

void print_state(StateMachine &stateMachine, WheelStateMachine &wheelStateMachine);
void print_lights(GuiLightPtr *lights);

void handle_input(int ch, StateMachine &stateMachine, WheelStateMachine &wheelStateMachine, int elapsedTimeMs);
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

  gui = new NCursesGui();

  gui->init();

  GuiLightPtr *lights = createLights();

  // Use a single generator to make sure that all lights get *different* random timings.
  // Seed is good enough for animating model house lights :D
  RandomGenerator randomGenerator(seconds_since_epoch());

  LightControllerPtr *lightControllers = createLightControllers(lights, NUMBER_OF_LIGHTS, &randomGenerator);

  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = sigIntReceived;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  circularActivator = new CircularActivator((AbstractLightControllerPtr *)lightControllers, NUMBER_OF_LIGHTS, 5);
  LightCollectionController lightCollectionController(lightControllers, circularActivator, NUMBER_OF_LIGHTS);

  StateMachine stateMachine(&lightCollectionController);
  WheelStateMachine wheelStateMachine(&lightCollectionController, &stateMachine);

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
      handle_input(ch, stateMachine, wheelStateMachine, elapsedTimeMs);
    }
    print_state(stateMachine, wheelStateMachine);
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

LightControllerPtr *createLightControllers(GuiLightPtr *lights, int count, RandomGenerator *randomGenerator) {
  LightControllerPtr *lightControllers = new LightControllerPtr[count];

  for (int i = 0 ; i < count ; i++) {
    LightController *lightController = new LightController(lights[i], randomGenerator, ON_TIME_DURATION, OFF_TIME_DURATION);

    lightControllers[i] = lightController;
  }

  return lightControllers;
}

void print_intro() {
  gui->print(0, (char *)"q: Quit\n");
  gui->print(0, (char *)"z: Turn off\n");
  gui->print(0, (char *)"x: Gradual\n");
  gui->print(0, (char *)"c: Turn on\n");
  gui->print(0, (char *)"\n");
  gui->print(0, (char *)"<space>: toggle cycling/speed mode\n");
  gui->print(0, (char *)"a: Cycle -2\n");
  gui->print(0, (char *)"s: Cycle -1\n");
  gui->print(0, (char *)"d: Cycle 1\n");
  gui->print(0, (char *)"f: Cycle 2\n");

  refresh();
}

void handle_input(int ch, StateMachine &stateMachine, WheelStateMachine &wheelStateMachine, int elapsedTimeMs) {
  switch(ch) {
  case 'z':
    stateMachine.switchOff();
    break;
  case 'x':
    stateMachine.switchGradual(elapsedTimeMs, GRADUAL_TRANSITION_PERIOD_MS);
    break;
  case 'c':
    stateMachine.switchOn();
    break;
  case ' ':
    wheelStateMachine.wheelPressed();
    break;
  case 'a':
    wheelStateMachine.wheelTurned(-2);
    break;
  case 's':
    wheelStateMachine.wheelTurned(-1);
    break;
  case 'd':
    wheelStateMachine.wheelTurned(1);
    break;
  case 'f':
    wheelStateMachine.wheelTurned(2);
    break;

  }
}

void print_state(StateMachine &stateMachine, WheelStateMachine &wheelStateMachine) {
  State state = stateMachine.getState();

  char description[60];

  switch (state) {
  case StateOff:
    strcpy(description, "StateOff");

    break;
  case StateTurningOn:
    strcpy(description, "StateTurningOn");
    break;
  case StateAnimating:
    strcpy(description, "StateAnimating");
    break;
  case StateOn:
    strcpy(description, "StateOn");
    break;
  case StateTurningOff:
    strcpy(description, "StateTurningOff");
    break;
  }

  gui->print(headerSize + 2, description);

  switch (wheelStateMachine.getState()) {
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
                wheelStateMachine.getSpeedRotation(),
                wheelStateMachine.getDelayFactor()
                );
        break;
  }

  gui->print(headerSize + 4, description);

  refresh();
}

void print_lights(GuiLightPtr *lights) {
  char line[NUMBER_OF_LIGHTS * 2 + 2];

  for (int i = 0 ; i < NUMBER_OF_LIGHTS ; i++ ) {
    GuiLightPtr pLight = (GuiLightPtr)lights[i];

    line[2*i] = pLight->getState() ? '*' : '.';
    line[2*i+1] = ' ';
  }
  line[NUMBER_OF_LIGHTS * 2] = '\n';

  gui->print(headerSize + 6, line);
}

int seconds_since_epoch() {
  auto start = std::chrono::system_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
}
