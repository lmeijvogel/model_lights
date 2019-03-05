#include "catch.hpp"
#include "../StateMachine.hpp"

TEST_CASE("StateMachine starts Off", "[StateMachine]") {
  StateMachine stateMachine;

  REQUIRE(stateMachine.getState() == StateOff);
}

TEST_CASE("When switched On, StateMachine becomes On", "[StateMachine]")
{
  StateMachine stateMachine;

  stateMachine.switchOn();
  
  REQUIRE(stateMachine.getState() == StateOn);
}


TEST_CASE("From On, switches to Off", "[StateMachine]")
{
  StateMachine stateMachine;

  stateMachine.switchOn();
  stateMachine.switchOff();
  
  REQUIRE(stateMachine.getState() == StateOff);
}


TEST_CASE("From Off, switches to TurningOn", "[StateMachine]")
{
  StateMachine stateMachine;

  stateMachine.switchGradual();
  
  REQUIRE(stateMachine.getState() == StateTurningOn);
}

TEST_CASE("From On, switches to TurningOff", "[StateMachine]")
{
  StateMachine stateMachine;

  stateMachine.switchOn();
  stateMachine.switchGradual();
  
  REQUIRE(stateMachine.getState() == StateTurningOff);
}

TEST_CASE("From Animating, switches to TurningOff", "[StateMachine]")
{
  StateMachine stateMachine;

  stateMachine._switchAnimatingForTest();
  stateMachine.switchGradual();
  
  REQUIRE(stateMachine.getState() == StateTurningOff);
}
// Off -> GradualOn -> auto Animating
// GradualOff -> auto Off
