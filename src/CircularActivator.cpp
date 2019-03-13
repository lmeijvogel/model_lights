#include "CircularActivator.h"
#include <stdio.h>

CircularActivator::CircularActivator(AbstractLightControllerPtr *lightControllers, int numberOfLights, int overflowNumber) {
  this->lightControllers = lightControllers;
  this->numberOfLights = numberOfLights;
  this->overflowNumber = overflowNumber;
  this->isActivating = true;
  this->isStarted = false;
}

void CircularActivator::advance(int steps) {
  int remaining = steps > 0 ? steps : -steps;

  int delta;
  if (steps > 0) {
    delta = 1;
  } else {
    delta = -1;
  }

  if (!isStarted) {
    isStarted = true;
    if (delta == 1) {
      currentLightIndex = 0;
    } else {
      currentLightIndex = numberOfLights - 1;
    }
  }

  int overflowBoundary = overflowNumber - 1;

  while (remaining > 0) {
    remaining--;

    bool inRange;
    bool inOverflow;

    if (delta == 1) {
      inRange = currentLightIndex < numberOfLights;
      inOverflow = numberOfLights <= currentLightIndex && currentLightIndex < numberOfLights + overflowBoundary;
    } else {
      inRange = 0 <= currentLightIndex;
      inOverflow = -overflowBoundary <= currentLightIndex && currentLightIndex < 0;
    }

    if (inRange) {
      toggleLight();
      currentLightIndex += delta;
    } else if (inOverflow) {
      currentLightIndex += delta;
    } else {
      if (delta == 1) {
        currentLightIndex = 0;
      } else {
        currentLightIndex = numberOfLights - 1;
      }
      isActivating = !isActivating;

      toggleLight();
    }
  }
}

void CircularActivator::toggleLight() {
  if (isActivating) {
    lightControllers[currentLightIndex]->setOn();
  } else {
    lightControllers[currentLightIndex]->setOff();
  }
}
