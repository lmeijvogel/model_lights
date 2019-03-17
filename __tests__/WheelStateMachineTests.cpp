#include "catch.hpp"

#include "../src/WheelStateMachine.h"
#include "MockLightController.h"

double truncatedDouble(double number) {
  return ((int)(number *100))/100.0;
}

TEST_CASE("Starts in cycling state", "[StateMachine]") {
  MockLightController lightController;

  WheelStateMachine wheelStateMachine(&lightController);

  REQUIRE(wheelStateMachine.getState() == StateCycling);

  wheelStateMachine.wheelTurned(2);

  REQUIRE(lightController.receivedCycle == 2);
}

TEST_CASE("Activating speed state", "[StateMachine]") {
  MockLightController lightController;
  WheelStateMachine wheelStateMachine(&lightController);

  wheelStateMachine.wheelPressed();

  REQUIRE(wheelStateMachine.getState() == StateSpeed);

  wheelStateMachine.wheelTurned(1);

  REQUIRE(truncatedDouble(lightController.receivedChangeDelay) == 0.9);

  wheelStateMachine.wheelTurned(1);

  REQUIRE(truncatedDouble(lightController.receivedChangeDelay) == 0.82);

  wheelStateMachine.wheelTurned(-1);

  REQUIRE(truncatedDouble(lightController.receivedChangeDelay) == 0.9);
}

TEST_CASE("Transition from speed back to cycling", "[StateMachine]") {
  MockLightController lightController;
  WheelStateMachine wheelStateMachine(&lightController);

  REQUIRE(wheelStateMachine.getState() == StateCycling);

  wheelStateMachine.wheelPressed();

  REQUIRE(wheelStateMachine.getState() == StateSpeed);

  wheelStateMachine.wheelPressed();

  REQUIRE(wheelStateMachine.getState() == StateCycling);
}
