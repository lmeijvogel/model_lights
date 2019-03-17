#include "catch.hpp"

#include "../src/WheelStateMachine.h"
#include "MockLightController.h"

class MockStateMachine : public Delayable {
public:
  virtual void changeDelay(double factor);

  double receivedChangeDelay;
};

void MockStateMachine::changeDelay(double factor) {
  this->receivedChangeDelay = factor;
}

double truncatedDouble(double number) {
  return ((int)(number *100))/100.0;
}

TEST_CASE("Starts in cycling state", "[StateMachine]") {
  MockLightController lightController;
  MockStateMachine mockStateMachine;

  WheelStateMachine wheelStateMachine(&lightController, &mockStateMachine);

  REQUIRE(wheelStateMachine.getState() == StateCycling);

  wheelStateMachine.wheelTurned(2);

  REQUIRE(lightController.receivedCycle == 2);
}

TEST_CASE("Activating speed state", "[StateMachine]") {
  MockLightController lightController;
  MockStateMachine mockStateMachine;

  WheelStateMachine wheelStateMachine(&lightController, &mockStateMachine);

  wheelStateMachine.wheelPressed();

  REQUIRE(wheelStateMachine.getState() == StateSpeed);

  wheelStateMachine.wheelTurned(1);

  REQUIRE(truncatedDouble(lightController.receivedChangeDelay) == 0.9);
  REQUIRE(truncatedDouble(mockStateMachine.receivedChangeDelay) == 0.9);

  wheelStateMachine.wheelTurned(1);

  REQUIRE(truncatedDouble(lightController.receivedChangeDelay) == 0.82);
  REQUIRE(truncatedDouble(lightController.receivedChangeDelay) == 0.82);

  wheelStateMachine.wheelTurned(-1);

  REQUIRE(truncatedDouble(lightController.receivedChangeDelay) == 0.9);
  REQUIRE(truncatedDouble(mockStateMachine.receivedChangeDelay) == 0.9);
}

TEST_CASE("Transition from speed back to cycling", "[StateMachine]") {
  MockLightController lightController;
  MockStateMachine mockStateMachine;

  WheelStateMachine wheelStateMachine(&lightController, &mockStateMachine);

  REQUIRE(wheelStateMachine.getState() == StateCycling);

  wheelStateMachine.wheelPressed();

  REQUIRE(wheelStateMachine.getState() == StateSpeed);

  wheelStateMachine.wheelPressed();

  REQUIRE(wheelStateMachine.getState() == StateCycling);
}
