// the setup function runs once when you press reset or power the board
#include "AbstractLightController.h"
#include "GuiLight.h"
#include "LightCollectionController.h"
#include "LightController.h"
#include "Light.h"
#include "LedLight.h"
#include "NullLightController.h"
#include "StateMachine.h"
#include "RandomGenerator.h"

typedef LightController* LightControllerPtr;
typedef LedLight* LedLightPtr;

const int NUMBER_OF_LIGHTS = 1;

unsigned long startTime;

LightControllerPtr *createLightControllers(LedLightPtr *lights, int count, RandomGenerator *randomGenerator);

LightCollectionController *lightCollectionController;
StateMachine *stateMachine;

void setup() {
  startTime = millis();

  RandomGenerator randomGenerator(startTime);

  LedLightPtr *lights[NUMBER_OF_LIGHTS];

  LedLightPtr light = new LedLight(LED_BUILTIN);

  lights[0] = &light;

  LightControllerPtr *lightControllers = createLightControllers(*lights, NUMBER_OF_LIGHTS, &randomGenerator);

  lightCollectionController = new LightCollectionController(lightControllers, NUMBER_OF_LIGHTS);

  stateMachine = new StateMachine(lightCollectionController);
  stateMachine->switchGradual(startTime, 1000);
}

// the loop function runs over and over again forever
void loop() {
  unsigned long now = millis();

  stateMachine->clockTick(now);

  lightCollectionController->clockTick(now);
}

LightControllerPtr *createLightControllers(LedLightPtr *lights, int count, RandomGenerator *randomGenerator) {
  LightControllerPtr *lightControllers = new LightControllerPtr[count];

  for (int i = 0 ; i < count ; i++) {
    LightController *lightController = new LightController(lights[i], randomGenerator, 5000, 5000);
    lightControllers[i] = lightController;
  }

  return lightControllers;
}
