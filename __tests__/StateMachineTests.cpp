#include "catch.hpp"
#include "../src/StateMachine.hpp"
#include "../src/AbstractLightsDriver.hpp"

const int TRANSITION_UNTIL_MS=60;

class MockLightsDriver : public AbstractLightsDriver {
public:
  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(int transitionTimeSeconds);
  virtual void gradualOff(int transitionTimeSeconds);

  bool receivedSetOn = false;
  bool receivedSetOff = false;
  bool receivedAnimating = false;
  int receivedGradualOn = 0;
  int receivedGradualOff = 0;
};

void MockLightsDriver::setOn() {
    this->receivedSetOn = true;
}

void MockLightsDriver::setOff() {
    this->receivedSetOff = true;
}

void MockLightsDriver::setAnimating() {
  this->receivedAnimating = true;
}

void MockLightsDriver::gradualOn(int transitionTimeSeconds) {
    this->receivedGradualOn = transitionTimeSeconds;
}

void MockLightsDriver::gradualOff(int transitionTimeSeconds) {
    this->receivedGradualOff = transitionTimeSeconds;
}

TEST_CASE("StateMachine starts Off", "[StateMachine]") {
  MockLightsDriver lightsDriver;

  StateMachine stateMachine(&lightsDriver);

  REQUIRE(stateMachine.getState() == StateOff);
}

TEST_CASE("When switched On, StateMachine becomes On", "[StateMachine]")
{
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine.switchOn();

  REQUIRE(stateMachine.getState() == StateOn);
  REQUIRE(lightsDriver.receivedSetOn);
}


TEST_CASE("From On, switches to Off", "[StateMachine]")
{
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine.switchOn();
  stateMachine.switchOff();

  REQUIRE(stateMachine.getState() == StateOff);
  REQUIRE(lightsDriver.receivedSetOff);
}


TEST_CASE("From Off, switches to TurningOn", "[StateMachine]")
{
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);
  REQUIRE(lightsDriver.receivedGradualOn == TRANSITION_UNTIL_MS);
}

TEST_CASE("From On, switches to TurningOff", "[StateMachine]")
{
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine.switchOn();
  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightsDriver.receivedGradualOff == TRANSITION_UNTIL_MS);
}

TEST_CASE("From TurningOn, pressing switchGradual moves to TurningOff", "[StateMachine]")
{
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightsDriver.receivedGradualOff == TRANSITION_UNTIL_MS);
}

TEST_CASE("From TurningOff, pressing switchGradual moves to TurningOn", "[StateMachine]")
{
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine.switchOn();
  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);
}

TEST_CASE("From Animating, switches to TurningOff", "[StateMachine]")
{
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine._switchAnimatingForTest();
  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOff);
  REQUIRE(lightsDriver.receivedGradualOff == TRANSITION_UNTIL_MS);
}

TEST_CASE("From TurningOn to Animating", "[StateMachine]") {
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

  stateMachine.switchGradual(TRANSITION_UNTIL_MS);

  REQUIRE(stateMachine.getState() == StateTurningOn);

  int tickDuration = 31;

  // Nothing changes at the first tick (timespan == 60s)
  stateMachine.clockTick(tickDuration);
  REQUIRE(stateMachine.getState() == StateTurningOn);

  // Past timespan, transition to animating
  stateMachine.clockTick(tickDuration*2);
  REQUIRE(stateMachine.getState() == StateAnimating);
  REQUIRE(lightsDriver.receivedAnimating == true);
}

TEST_CASE("From TurningOff to Off", "[StateMachine]") {
  MockLightsDriver lightsDriver;
  StateMachine stateMachine(&lightsDriver);

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
  REQUIRE(lightsDriver.receivedSetOff == true);
}

// GradualOff -> auto Off
