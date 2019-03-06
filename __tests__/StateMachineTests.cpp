#include "catch.hpp"
#include "../src/StateMachine.hpp"
#include "../src/AbstractLightsDriver.hpp"

int GRADUAL_TIMESPAN = 60;

class MockLightsDriver : public AbstractLightsDriver {
public:
  virtual void setOn();
  virtual void setOff();
  virtual void gradualOn(int transitionTimeSeconds);
  virtual void gradualOff(int transitionTimeSeconds);

  bool receivedSetOn;
  bool receivedSetOff;
  int receivedGradualOn;
  int receivedGradualOff;
};

void MockLightsDriver::setOn() {
    this->receivedSetOn = true;
}

void MockLightsDriver::setOff() {
    this->receivedSetOff = true;
}

void MockLightsDriver::gradualOn(int transitionTimeSeconds) {
    this->receivedGradualOn = transitionTimeSeconds;
}

void MockLightsDriver::gradualOff(int transitionTimeSeconds) {
    this->receivedGradualOff = transitionTimeSeconds;
}


MockLightsDriver lightsDriver;

TEST_CASE("StateMachine starts Off", "[StateMachine]") {
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  REQUIRE(stateMachine.getState() == StateOff);
}

TEST_CASE("When switched On, StateMachine becomes On", "[StateMachine]")
{
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  stateMachine.switchOn();

  REQUIRE(stateMachine.getState() == StateOn);
  REQUIRE(lightsDriver.receivedSetOn);
}


TEST_CASE("From On, switches to Off", "[StateMachine]")
{
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  stateMachine.switchOn();
  stateMachine.switchOff();

  REQUIRE(stateMachine.getState() == StateOff);
  REQUIRE(lightsDriver.receivedSetOff);
}


TEST_CASE("From Off, switches to TurningOn", "[StateMachine]")
{
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  stateMachine.switchGradual();

  REQUIRE(stateMachine.getState() == StateTurningOn);
  REQUIRE(lightsDriver.receivedGradualOn == GRADUAL_TIMESPAN);
}

TEST_CASE("From On, switches to TurningOff", "[StateMachine]")
{
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  stateMachine.switchOn();
  stateMachine.switchGradual();

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightsDriver.receivedGradualOff == GRADUAL_TIMESPAN);
}

TEST_CASE("From TurningOn, pressing switchGradual moves to TurningOff", "[StateMachine]")
{
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  stateMachine.switchGradual();

  REQUIRE(stateMachine.getState() == StateTurningOn);

  stateMachine.switchGradual();

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightsDriver.receivedGradualOff == GRADUAL_TIMESPAN);
}

TEST_CASE("From TurningOff, pressing switchGradual moves to TurningOn", "[StateMachine]")
{
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  stateMachine.switchOn();
  stateMachine.switchGradual();

  REQUIRE(stateMachine.getState() == StateTurningOff);

  stateMachine.switchGradual();

  REQUIRE(stateMachine.getState() == StateTurningOn);
}

TEST_CASE("From Animating, switches to TurningOff", "[StateMachine]")
{
  StateMachine stateMachine(&lightsDriver, GRADUAL_TIMESPAN);

  stateMachine._switchAnimatingForTest();
  stateMachine.switchGradual();

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightsDriver.receivedGradualOff == GRADUAL_TIMESPAN);
}
// Off -> GradualOn -> auto Animating
// GradualOff -> auto Off
