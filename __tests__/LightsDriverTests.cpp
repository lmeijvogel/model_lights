#include "catch.hpp"
#include "../src/LightsDriver.hpp"
#include "../src/Light.hpp"

class MockLight : public Light {
public:
  virtual void turnOn();
  virtual void turnOff();

  bool isOn;
};

void MockLight::turnOn() {
  isOn = true;
}
void MockLight::turnOff() {
  isOn = false;
}

typedef MockLight* MockLightPtr;

TEST_CASE("LightsDriver starts in state Unknown", "[LightsDriver]") {
  const int count = 10;
  LightPtr *lights = new LightPtr[10];

  for (int i = 0 ; i < 10 ; i++) {
    MockLightPtr mockLight = new MockLight;
    lights[i] = mockLight;
  }

  SECTION("LightsDriver starts in state Unknown", "[LightsDriver]") {
    LightsDriver lightsDriver((Light **)lights, count);

    REQUIRE(lightsDriver.getState() == LightsStateUnknown);
  }

  SECTION("LightsDriver turns off all lights", "[LightsDriver") {
    LightsDriver lightsDriver((Light **)lights, count);

    lightsDriver.setOn();
    lightsDriver.setOff();

    REQUIRE(lightsDriver.getState() == LightsOff);

    for (int i = 0 ; i < count ; i++) {
      MockLightPtr pLight = (MockLightPtr)lights[i];

      REQUIRE(!pLight->isOn);
    }
  }

  SECTION("LightsDriver turns on all lights", "[LightsDriver") {
    LightsDriver lightsDriver((Light **)lights, count);

    lightsDriver.setOn();

    REQUIRE(lightsDriver.getState() == LightsOn);

    for (int i = 0 ; i < count ; i++) {
      MockLightPtr pLight = (MockLightPtr)lights[i];

      REQUIRE(pLight->isOn);
    }
  }
}
