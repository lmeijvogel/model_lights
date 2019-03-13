#ifndef CIRCULAR_ACTIVATOR_H
#define CIRCULAR_ACTIVATOR_H

#include "AbstractLightController.h"

typedef AbstractLightController* AbstractLightControllerPtr;

class CircularActivator {
public:
  CircularActivator(AbstractLightControllerPtr *lightControllers, int numberOfLights, int overflowNumber);

  void advance(int count);
private:
  AbstractLightControllerPtr *lightControllers;
  int numberOfLights;
  int overflowNumber;
  bool isActivating;
  bool isStarted;

  int currentLightIndex = 0;

  void toggleLight();
};

#endif
