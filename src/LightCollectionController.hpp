#ifndef LIGHT_COLLECTION_CONTROLLER_H
#define LIGHT_COLLECTION_CONTROLLER_H

#include <functional>

#include "AbstractLightController.hpp"
#include "LightController.hpp"

typedef LightController* LightControllerPtr;

class LightCollectionController : public AbstractLightController {
public:
  LightCollectionController(LightControllerPtr lightControllers[], int count);
  virtual LightsState getState();

  virtual void setOn();
  virtual void setOff();
  virtual void setAnimating();
  virtual void gradualOn(int transitionUntilMs);
  virtual void gradualOff(int transitionUntilMs);

  virtual void clockTick(int currentTimeMs);

private:
  LightControllerPtr *lightControllers;
  int count;

  LightsState state = LightsStateUnknown;

  void forEachLight(std::function<void (LightControllerPtr)> func);
};
#endif
