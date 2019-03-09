#include "catch.hpp"
#include "../src/LightCollectionController.hpp"
#include "../src/LightController.hpp"

#include "MockLightController.hpp"

typedef MockLightController* MockLightControllerPtr;

const int TRANSITION_UNTIL_MS = 60;

TEST_CASE("LightCollectionController starts in state Unknown", "[LightCollectionController]") {
  const int count = 10;
  MockLightControllerPtr *lightControllers = new MockLightControllerPtr[10];

  for (int i = 0 ; i < 10 ; i++) {
    MockLightControllerPtr mockLightController = new MockLightController;
    lightControllers[i] = mockLightController;
  }

  SECTION("LightCollectionController starts in state Unknown", "[LightCollectionController]") {
    LightCollectionController lightCollectionController((LightController **)lightControllers, count);

    REQUIRE(lightCollectionController.getState() == LightsStateUnknown);
  }

  SECTION("LightCollectionController turns off all lightControllers", "[LightCollectionController") {
    LightCollectionController lightCollectionController((LightController **)lightControllers, count);

    lightCollectionController.setOn();
    lightCollectionController.setOff();

    REQUIRE(lightCollectionController.getState() == LightsOff);

    for (int i = 0 ; i < count ; i++) {
      MockLightControllerPtr pLightController = (MockLightControllerPtr)lightControllers[i];

      REQUIRE(pLightController->receivedSetOff);
    }
  }

  SECTION("LightCollectionController turns on all lightControllers", "[LightCollectionController") {
    LightCollectionController lightCollectionController((LightController **)lightControllers, count);

    lightCollectionController.setOn();

    REQUIRE(lightCollectionController.getState() == LightsOn);

    for (int i = 0 ; i < count ; i++) {
      MockLightControllerPtr pLightController = (MockLightControllerPtr)lightControllers[i];

      REQUIRE(pLightController->receivedSetOn);
    }
  }

  SECTION("LightCollectionController gradually turns on all lightControllers", "[LightCollectionController") {
    LightCollectionController lightCollectionController((LightController **)lightControllers, count);

    lightCollectionController.gradualOn(TRANSITION_UNTIL_MS);

    REQUIRE(lightCollectionController.getState() == LightsTurningOn);

    for (int i = 0 ; i < count ; i++) {
      MockLightControllerPtr pLightController = (MockLightControllerPtr)lightControllers[i];

      REQUIRE(pLightController->receivedGradualOn == TRANSITION_UNTIL_MS);
    }
  }

  SECTION("LightCollectionController gradually turns off all lightControllers", "[LightCollectionController") {
    LightCollectionController lightCollectionController((LightController **)lightControllers, count);

    lightCollectionController.gradualOff(TRANSITION_UNTIL_MS);

    REQUIRE(lightCollectionController.getState() == LightsTurningOff);

    for (int i = 0 ; i < count ; i++) {
      MockLightControllerPtr pLightController = (MockLightControllerPtr)lightControllers[i];

      REQUIRE(pLightController->receivedGradualOff == TRANSITION_UNTIL_MS);
    }
  }
}