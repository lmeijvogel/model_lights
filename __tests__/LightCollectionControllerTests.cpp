#include "catch.hpp"
#include "../src/LightCollectionController.hpp"
#include "../src/Light.hpp"

class MockLight : public Light {
public:
  virtual void turnOn();
  virtual void turnOff();
  virtual void gradualOn(int transitionUntilMs);
  virtual void gradualOff(int transitionUntilMs);

  bool isOn = false;
  bool isGraduallyTurningOn = false;
  bool isGraduallyTurningOff = false;
};

void MockLight::turnOn() {
  isOn = true;
}
void MockLight::turnOff() {
  isOn = false;
}

void MockLight::gradualOn(int transitionUntilMs) {
  isGraduallyTurningOn = true;
}

void MockLight::gradualOff(int transitionUntilMs) {
  isGraduallyTurningOff = true;
}

typedef MockLight* MockLightPtr;

const int TRANSITION_UNTIL_MS = 60;

TEST_CASE("LightCollectionController starts in state Unknown", "[LightCollectionController]") {
  const int count = 10;
  LightPtr *lights = new LightPtr[10];

  for (int i = 0 ; i < 10 ; i++) {
    MockLightPtr mockLight = new MockLight;
    lights[i] = mockLight;
  }

  SECTION("LightCollectionController starts in state Unknown", "[LightCollectionController]") {
    LightCollectionController lightCollectionController((Light **)lights, count);

    REQUIRE(lightCollectionController.getState() == LightsStateUnknown);
  }

  SECTION("LightCollectionController turns off all lights", "[LightCollectionController") {
    LightCollectionController lightCollectionController((Light **)lights, count);

    lightCollectionController.setOn();
    lightCollectionController.setOff();

    REQUIRE(lightCollectionController.getState() == LightsOff);

    for (int i = 0 ; i < count ; i++) {
      MockLightPtr pLight = (MockLightPtr)lights[i];

      REQUIRE(!pLight->isOn);
    }
  }

  SECTION("LightCollectionController turns on all lights", "[LightCollectionController") {
    LightCollectionController lightCollectionController((Light **)lights, count);

    lightCollectionController.setOn();

    REQUIRE(lightCollectionController.getState() == LightsOn);

    for (int i = 0 ; i < count ; i++) {
      MockLightPtr pLight = (MockLightPtr)lights[i];

      REQUIRE(pLight->isOn);
    }
  }

  SECTION("LightCollectionController gradually turns on all lights", "[LightCollectionController") {
    LightCollectionController lightCollectionController((Light **)lights, count);

    lightCollectionController.gradualOn(TRANSITION_UNTIL_MS);

    REQUIRE(lightCollectionController.getState() == LightsTurningOn);

    for (int i = 0 ; i < count ; i++) {
      MockLightPtr pLight = (MockLightPtr)lights[i];

      REQUIRE(pLight->isGraduallyTurningOn);
    }
  }

  SECTION("LightCollectionController gradually turns off all lights", "[LightCollectionController") {
    LightCollectionController lightCollectionController((Light **)lights, count);

    lightCollectionController.gradualOff(TRANSITION_UNTIL_MS);

    REQUIRE(lightCollectionController.getState() == LightsTurningOff);

    for (int i = 0 ; i < count ; i++) {
      MockLightPtr pLight = (MockLightPtr)lights[i];

      REQUIRE(pLight->isGraduallyTurningOff);
    }
  }
}
