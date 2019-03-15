#include "catch.hpp"

#include "../src/WheelStateMachine.h"
#include "MockLightController.h"

TEST_CASE("Starts in cycling state", "[StateMachine]") {
  MockLightController lightController;

  WheelStateMachine stateMachine(&lightController);

  REQUIRE(stateMachine.getState() == StateCycling);

  stateMachine.wheelTurned(2);

  REQUIRE(lightController.receivedCycle == 2);
}

TEST_CASE("Activating speed state", "[StateMachine]") {
  MockLightController lightController;
  WheelStateMachine stateMachine(&lightController);

  stateMachine.wheelPressed();

  REQUIRE(stateMachine.getState() == StateSpeed);

  stateMachine.wheelTurned(2);

  REQUIRE(lightController.receivedCycle == 2);
}

TEST_CASE("Transition from speed back to cycling", "[StateMachine]") {
  MockLightController lightController;
  WheelStateMachine stateMachine(&lightController);

  REQUIRE(stateMachine.getState() == StateCycling);

  stateMachine.wheelPressed();

  REQUIRE(stateMachine.getState() == StateSpeed);

  stateMachine.wheelPressed();

  REQUIRE(stateMachine.getState() == StateCycling);
}
