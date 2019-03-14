#include "CircularActivator.h"
#include "NullLightController.h"
#include <stdio.h>

CircularActivator::CircularActivator(AbstractLightControllerPtr *lightControllers, int numberOfLights, int overflowNumber) {
  createLightControllersWithOverflow(lightControllers, numberOfLights, overflowNumber);

  this->numberOfLights = numberOfLights;
  this->overflowNumber = overflowNumber;
  this->isActivating = true;
  this->isStarted = false;
}

void CircularActivator::advance(int steps) {
  int totalArraySize = numberOfLights + overflowNumber;

  int remaining = steps > 0 ? steps : -steps;
  int delta = steps > 0 ? 1 : -1;

  // If we're moving in the opposite direction, we want any lights that were turned on
  // to be turned off again and vice versa
  if (delta == -previousDelta) {
    this->isActivating = !this->isActivating;
    advancePointer(delta);
  }

  if (!isStarted) {
    isStarted = true;
    if (delta == 1) {
      currentLightIndex = overflowNumber;
    } else {
      currentLightIndex = totalArraySize - 1;
    }
  }

  while (remaining > 0) {
    remaining--;

    toggleLight();

    advancePointer(delta);
  }

  previousDelta = delta;
}

void CircularActivator::createLightControllersWithOverflow(AbstractLightControllerPtr *lightControllers, int numberOfLights, int overflowNumber) {
  int totalSize = numberOfLights + overflowNumber;
  this->lightControllers = new AbstractLightControllerPtr[totalSize];

  for (int i = 0 ; i < overflowNumber ; i++) {
    this->lightControllers[i] = new NullLightController();
  }
  for (int i = 0 ; i < numberOfLights ; i++) {
    this->lightControllers[i+overflowNumber] = lightControllers[i];
  }

}

void CircularActivator::toggleLight() {
  if (isActivating) {
    lightControllers[currentLightIndex]->setOn();
  } else {
    lightControllers[currentLightIndex]->setOff();
  }
}

void CircularActivator::advancePointer(int delta) {
  int totalArraySize = numberOfLights + overflowNumber;

  currentLightIndex += delta;

  if (currentLightIndex < 0) {
    currentLightIndex = totalArraySize - 1;
    isActivating = !isActivating;
  } else if (currentLightIndex > totalArraySize - 1) {
    currentLightIndex = 0;
    isActivating = !isActivating;
  }
}

int CircularActivator::getCurrentLightIndex() {
  return currentLightIndex;
}

bool CircularActivator::getIsActivating() {
  return isActivating;
}
