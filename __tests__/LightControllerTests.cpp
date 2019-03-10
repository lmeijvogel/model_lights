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

  LightController lightController(&mockLight, &randomGenerator);

  lightController.setOn();

  REQUIRE(mockLight.isOn);
}

TEST_CASE("When it receives setOff(), turns off the light") {
  MockLight mockLight;

  LightController lightController(&mockLight, &randomGenerator);

  lightController.setOn();

  REQUIRE(mockLight.isOn);

  lightController.setOff();

  REQUIRE(!mockLight.isOn);
}
