#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <ncurses.h>
#include "StateMachine.hpp"
#include "NullLightsDriver.hpp"

void print_intro();

void print_state(StateMachine &stateMachine);

void handle_input(int ch, StateMachine &stateMachine);

void cleanupAndExit() {
  endwin();

  exit(1);
}

void sigIntReceived(int s) {
  cleanupAndExit();
}

int main() {
  initscr();

  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = sigIntReceived;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  NullLightsDriver nullLightsDriver;
  StateMachine stateMachine(&nullLightsDriver, 60);

  print_intro();
  cbreak();
  noecho();

  refresh();

  while (true) {
    int ch = getch();

    if (ch == 'q') {

      cleanupAndExit();
    } else {
      handle_input(ch, stateMachine);
      print_state(stateMachine);

      refresh();
    }
  }

  cleanupAndExit();
  return 0;
}

void print_intro() {
  printw("q: Quit\n");
  printw("z: Turn off\n");
  printw("x: Gradual\n");
  printw("c: Turn on\n");
  refresh();
}

void handle_input(int ch, StateMachine &stateMachine) {
  switch(ch) {
  case 'z':
    stateMachine.switchOff();
    break;
  case 'x':
    stateMachine.switchGradual();
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
