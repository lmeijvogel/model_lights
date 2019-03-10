#include "../src/Light.hpp"

// the setup function runs once when you press reset or power the board
#include "AbstractLightController.hpp"
#include "GuiLight.hpp"
#include "LightCollectionController.hpp"
#include "LightController.hpp"
#include "Light.hpp"
#include "LedLight.hpp"
#include "NullLightController.hpp"
#include "StateMachine.hpp"
#include "RandomGenerator.hpp"

typedef LightController* LightControllerPtr;
typedef LedLight* LedLightPtr;

const int NUMBER_OF_LIGHTS = 1;

int startTime;

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
}

// the loop function runs over and over again forever
void loop() {
  auto now = millis();

  int elapsedTimeMs = now - startTime;

  stateMachine->clockTick(elapsedTimeMs);

  lightCollectionController->clockTick(elapsedTimeMs);
}

LightControllerPtr *createLightControllers(LedLightPtr *lights, int count, RandomGenerator *randomGenerator) {
  LightControllerPtr *lightControllers = new LightControllerPtr[count];

  for (int i = 0 ; i < count ; i++) {
    LightController *lightController = new LightController(lights[i], randomGenerator);
    lightControllers[i] = lightController;
  }

  return lightControllers;
}
