#ifndef CIRCULAR_ACTIVATOR_H
#define CIRCULAR_ACTIVATOR_H

#include "AbstractLightController.h"

typedef AbstractLightController* AbstractLightControllerPtr;

class CircularActivator {
public:
  CircularActivator(AbstractLightControllerPtr *lightControllers, int numberOfLights, int overflowNumber);

  void advance(int count);

  int getCurrentLightIndex();
  bool getIsActivating();

private:
  void createLightControllersWithOverflow(AbstractLightControllerPtr *lightControllers, int numberOfLights, int overflowNumber);

  AbstractLightControllerPtr *lightControllers;
  int numberOfLights;
  int overflowNumber;
  bool isActivating;
  bool isStarted;

  int currentLightIndex = 0;
  int previousDelta = 0;

  void toggleLight();
  void advancePointer(int delta);
};

#endif
