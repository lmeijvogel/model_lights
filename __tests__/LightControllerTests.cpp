#include "catch.hpp"
#include "../src/LightController.h"
#include "../src/Light.h"
#include "../src/RandomGenerator.h"

class MockLight : public Light {
public:
  virtual void turnOn();
  virtual void turnOff();

  bool isOn = false;
};

void MockLight::turnOn() {
  isOn = true;
}

void MockLight::turnOff() {
  isOn = false;
}

RandomGenerator randomGenerator(0);

TEST_CASE("When it receives setOn(), turns on the light") {
  MockLight mockLight;

  LightController lightController(&mockLight, &randomGenerator, 0, 0);

  lightController.setOn();

  REQUIRE(mockLight.isOn);
}

TEST_CASE("When it receives setOff(), turns off the light") {
  MockLight mockLight;

  LightController lightController(&mockLight, &randomGenerator, 0, 0);

  lightController.setOn();

  REQUIRE(mockLight.isOn);

  lightController.setOff();

  REQUIRE(!mockLight.isOn);
}

TEST_CASE("When one of the LightControllers gradually switches, does not affect the others") {
  MockLight mockLight;

  LightController lightController1(&mockLight, &randomGenerator, 0, 0);
  LightController lightController2(&mockLight, &randomGenerator, 0, 0);

  lightController1.gradualOn(10, 10);

  REQUIRE(lightController2._nextEventForTests().referenceTimestampMs == 0);
}
