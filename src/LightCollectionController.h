#ifndef LIGHT_COLLECTION_CONTROLLER_H
#define LIGHT_COLLECTION_CONTROLLER_H

#include "AbstractLightController.h"
#include "CircularActivator.h"
#include "LightController.h"

typedef LightController* LightControllerPtr;

class LightCollectionController : public AbstractLightController {
public:
  LightCollectionController(LightControllerPtr lightControllers[], CircularActivator *circularActivator, int count);
  virtual LightsState getState();

  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(unsigned long currentTimeMs, unsigned long transitionTimeMs);
  virtual void gradualOff(unsigned long currentTimeMs, unsigned long transitionTimeMs);

  virtual void cycle(int steps);
  virtual void changeDelay(double factor);

  virtual void clockTick(unsigned long currentTimeMs);

private:
  LightControllerPtr *lightControllers;
  CircularActivator *circularActivator;
  int count;

  LightsState state = LightsStateUnknown;
};
#endif
