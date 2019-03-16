#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "AbstractLightController.h"
#include "Light.h"
#include "RandomGenerator.h"

enum LightControllerState {
                           LightControllerOff,
                           LightControllerTurningOn,
                           LightControllerAnimating,
                           LightControllerTurningOff,
                           LightControllerOn
};

struct LightControllerEvent {
  LightControllerState state;
  unsigned long referenceTimestampMs;
  unsigned long periodAfterReferenceMs;
};

class LightController : public AbstractLightController {
public:
  LightController(Light *pLight, RandomGenerator *randomGenerator, unsigned long onTimeDurationMs, unsigned long offTimeDurationMs);

  virtual ~LightController();

  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void cycle(int);

  virtual void clockTick(unsigned long currentTimeMs);

  virtual LightControllerEvent _nextEventForTests();
private:
  Light *pLight;
  RandomGenerator *randomGenerator;

  bool lightIsOn = false;
  LightControllerState state;

  unsigned long onTimeDurationMs;
  unsigned long offTimeDurationMs;

  LightControllerEvent *nextEvent;

  void handleAnimating(unsigned long currentTimeMs);

  void scheduleNextEvent(LightControllerState state, unsigned long currentTimeMs, unsigned long meanDurationMs);

  bool isNextEventScheduled();
  void clearNextEvent();

  void _turnOnLight();
  void _turnOffLight();
};
#endif
