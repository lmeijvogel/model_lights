#include "catch.hpp"
#include "../src/StateMachine.h"
#include "../src/AbstractLightController.h"

#include "MockLightController.h"

const int TRANSITION_UNTIL_MS=60;

TEST_CASE("StateMachine starts Off", "[StateMachine]") {
  MockLightController lightController;

  StateMachine stateMachine(&lightController);

  REQUIRE(stateMachine.getState() == StateOff);
}

TEST_CASE("When switched On, StateMachine becomes On", "[StateMachine]")
{
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchOn();

  REQUIRE(stateMachine.getState() == StateOn);
  REQUIRE(lightController.receivedSetOn);
}


TEST_CASE("From On, switches to Off", "[StateMachine]")
{
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchOn();
  stateMachine.switchOff();

  REQUIRE(stateMachine.getState() == StateOff);
  REQUIRE(lightController.receivedSetOff);
}


TEST_CASE("From Off, switches to TurningOn", "[StateMachine]")
{
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);
  REQUIRE(lightController.receivedGradualOn == TRANSITION_UNTIL_MS);
}

TEST_CASE("From On, switches to TurningOff", "[StateMachine]")
{
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchOn();
  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightController.receivedGradualOff == TRANSITION_UNTIL_MS);
}

TEST_CASE("From TurningOn, pressing switchGradual moves to TurningOff", "[StateMachine]")
{
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightController.receivedGradualOff == TRANSITION_UNTIL_MS);
}

TEST_CASE("From TurningOff, pressing switchGradual moves to TurningOn", "[StateMachine]")
{
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchOn();
  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);
}

TEST_CASE("From Animating, switches to TurningOff", "[StateMachine]")
{
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine._switchAnimatingForTest();
  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightController.receivedGradualOff == TRANSITION_UNTIL_MS);
}

TEST_CASE("From TurningOn to Animating", "[StateMachine]") {
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);

  int tickDuration = 31;

  // Nothing changes at the first tick (timespan == 60s)
  stateMachine.clockTick(tickDuration);
  REQUIRE(stateMachine.getState() == StateTurningOn);

  // Past timespan, transition to animating
  stateMachine.clockTick(tickDuration*2);
  REQUIRE(stateMachine.getState() == StateAnimating);
  REQUIRE(lightController.receivedAnimating == true);
}

TEST_CASE("From TurningOff to Off", "[StateMachine]") {
  MockLightController lightController;
  StateMachine stateMachine(&lightController);

  stateMachine.switchOn();
  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);

  int tickDuration = 31;

  // Nothing changes at the first tick (timespan == 60s)
  stateMachine.clockTick(tickDuration);
  REQUIRE(stateMachine.getState() == StateTurningOff);

  // Past timespan, transition to off
  stateMachine.clockTick(tickDuration*2);
  REQUIRE(stateMachine.getState() == StateOff);
  REQUIRE(lightController.receivedSetOff == true);
}

// GradualOff -> auto Off
