#include "catch.hpp"

#include "../src/CircularActivator.h"
#include "MockLightController.h"

const int NUMBER_OF_LIGHTS = 5;
const int OVERFLOW_NUMBER = 3;

typedef MockLightController* MockLightControllerPtr;

TEST_CASE("Advancing") {
  MockLightControllerPtr *createLightControllers();

  MockLightControllerPtr *lightControllers = createLightControllers();
  AbstractLightControllerPtr *abstractLightControllers = (AbstractLightControllerPtr *)lightControllers;

  CircularActivator activator(abstractLightControllers, NUMBER_OF_LIGHTS, OVERFLOW_NUMBER);

  SECTION("when the first light is activated") {
    activator.advance(1);

    REQUIRE(lightControllers[0]->receivedSetOn);
  }

  SECTION("when the first and second light are activated, turns them on") {
    activator.advance(1);

    REQUIRE(lightControllers[0]->receivedSetOn);
    REQUIRE(!lightControllers[1]->receivedSetOn);

    activator.advance(1);

    REQUIRE(lightControllers[0]->receivedSetOn);
    REQUIRE(lightControllers[1]->receivedSetOn);
  }

  SECTION("when multiple steps are taken at the same time, turns all relevant lights on") {
    activator.advance(4);

    REQUIRE(lightControllers[0]->receivedSetOn);
    REQUIRE(lightControllers[1]->receivedSetOn);
    REQUIRE(lightControllers[2]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOn);
    REQUIRE(!lightControllers[4]->receivedSetOn);
  }

  SECTION("when more steps were taken than there are lights, within the overflow, turn on all of them") {
    activator.advance(7);

    REQUIRE(lightControllers[0]->receivedSetOn);
    REQUIRE(lightControllers[1]->receivedSetOn);
    REQUIRE(lightControllers[2]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOn);
    REQUIRE(lightControllers[4]->receivedSetOn);
  }

  SECTION("when more steps were taken than there are lights, past the overflow, turn on all of them, and turn off from the start") {
    activator.advance(10);

    REQUIRE(lightControllers[0]->receivedSetOff);
    REQUIRE(lightControllers[1]->receivedSetOff);
    REQUIRE(lightControllers[2]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOn);
    REQUIRE(lightControllers[4]->receivedSetOn);
  }

  SECTION("when all lights were turned off, turn them on again on the next round") {
    activator.advance(16);

    REQUIRE(lightControllers[0]->receivedSetOff);
    REQUIRE(lightControllers[1]->receivedSetOff);
    REQUIRE(lightControllers[2]->receivedSetOff);
    REQUIRE(lightControllers[3]->receivedSetOff);
    REQUIRE(lightControllers[4]->receivedSetOff);

    for (int i = 0 ; i < NUMBER_OF_LIGHTS; i++) {
      lightControllers[i]->receivedSetOn = false;
    }

    activator.advance(3);

    REQUIRE(lightControllers[0]->receivedSetOn);
    REQUIRE(lightControllers[1]->receivedSetOn);
    REQUIRE(lightControllers[2]->receivedSetOn);
  }
}

TEST_CASE("Receding") {
  MockLightControllerPtr *createLightControllers();

  MockLightControllerPtr *lightControllers = createLightControllers();
  AbstractLightControllerPtr *abstractLightControllers = (AbstractLightControllerPtr *)lightControllers;

  CircularActivator activator(abstractLightControllers, NUMBER_OF_LIGHTS, OVERFLOW_NUMBER);

  SECTION("when the last light is activated") {
    activator.advance(-1);

    REQUIRE(lightControllers[4]->receivedSetOn);
  }

  SECTION("when the first and second light are activated, turns them on") {
    activator.advance(-1);

    REQUIRE(lightControllers[4]->receivedSetOn);
    REQUIRE(!lightControllers[3]->receivedSetOn);

    activator.advance(-1);

    REQUIRE(lightControllers[4]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOn);
  }

  SECTION("when multiple steps are taken at the same time, turns all relevant lights on") {
    activator.advance(-4);

    REQUIRE(!lightControllers[0]->receivedSetOn);
    REQUIRE(lightControllers[1]->receivedSetOn);
    REQUIRE(lightControllers[2]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOn);
    REQUIRE(lightControllers[4]->receivedSetOn);
  }

  SECTION("when more steps were taken than there are lights, within the overflow, turn on all of them") {
    activator.advance(-7);

    REQUIRE(lightControllers[0]->receivedSetOn);
    REQUIRE(lightControllers[1]->receivedSetOn);
    REQUIRE(lightControllers[2]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOn);
    REQUIRE(lightControllers[4]->receivedSetOn);
  }

  SECTION("when more steps were taken than there are lights, past the overflow, turn on all of them, and turn off from the start") {
    // Go through overflow twice
    activator.advance(-10);

    REQUIRE(lightControllers[0]->receivedSetOn);
    REQUIRE(lightControllers[1]->receivedSetOn);
    REQUIRE(lightControllers[2]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOff);
    REQUIRE(lightControllers[4]->receivedSetOff);
  }

  SECTION("when all lights were turned off, turn them on again on the next round") {
    activator.advance(-16);

    REQUIRE(lightControllers[0]->receivedSetOff);
    REQUIRE(lightControllers[1]->receivedSetOff);
    REQUIRE(lightControllers[2]->receivedSetOff);
    REQUIRE(lightControllers[3]->receivedSetOff);
    REQUIRE(lightControllers[4]->receivedSetOff);

    for (int i = 0 ; i < NUMBER_OF_LIGHTS; i++) {
      lightControllers[i]->receivedSetOn = false;
    }

    activator.advance(-3);

    REQUIRE(lightControllers[2]->receivedSetOn);
    REQUIRE(lightControllers[3]->receivedSetOn);
    REQUIRE(lightControllers[4]->receivedSetOn);
  }
}

MockLightControllerPtr *createLightControllers() {
  MockLightControllerPtr *result = new MockLightControllerPtr[NUMBER_OF_LIGHTS];

  for (int i = 0 ; i < NUMBER_OF_LIGHTS ; i++) {
    result[i] = new MockLightController();
  }

  return result;
}
