// the setup function runs once when you press reset or power the board
#include "LightCollectionController.h"
#include "LightController.h"
#include "LedLight.h"
#include "StateMachine.h"
#include "RandomGenerator.h"
#include "PhysicalButton.h"

typedef LightController* LightControllerPtr;
typedef LedLight* LedLightPtr;

const int NUMBER_OF_LIGHTS = 4;
const int NUMBER_OF_BUTTONS = 2;

unsigned long startTime;

LightControllerPtr *createLightControllers(LedLightPtr *lights, int count, RandomGenerator *randomGenerator);
LedLightPtr *createLights(int *lightIds);

void pollButtons(unsigned long currentTimeMs);
void readButtons(StateMachine *stateMachine, unsigned long currentTimeMs);
void showStatus(State state);

LightCollectionController *lightCollectionController;
StateMachine *stateMachine;

PhysicalButton *gradualButton;
PhysicalButton *offButton;

LedLight *statusLight;

void setup() {
  statusLight = new LedLight(LED_BUILTIN);

  startTime = millis();

  RandomGenerator randomGenerator(startTime);

  int gradualButtonId = 2;
  int offButtonId = 4;

  gradualButton = new PhysicalButton(gradualButtonId);
  offButton = new PhysicalButton(offButtonId);

  int lightIds[NUMBER_OF_LIGHTS];
  lightIds[0] = 8;
  lightIds[1] = 9;
  lightIds[2] = 10;
  lightIds[3] = 11;

  LedLightPtr *lights = createLights(lightIds);

  LightControllerPtr *lightControllers = createLightControllers(lights, NUMBER_OF_LIGHTS, &randomGenerator);

  lightCollectionController = new LightCollectionController(lightControllers, NUMBER_OF_LIGHTS);

  stateMachine = new StateMachine(lightCollectionController);
  stateMachine->switchOff();
}

// the loop function runs over and over again forever
void loop() {
  unsigned long now = millis();

  pollButtons(now);
  readButtons(stateMachine, now);

  stateMachine->clockTick(now);

  showStatus(stateMachine->getState());

  lightCollectionController->clockTick(now);
}

LightControllerPtr *createLightControllers(LedLightPtr *lights, int count, RandomGenerator *randomGenerator) {
  LightControllerPtr *lightControllers = new LightControllerPtr[count];

  for (int i = 0 ; i < count ; i++) {
    LightController *lightController = new LightController(lights[i], randomGenerator, 5000, 3000);
    lightControllers[i] = lightController;
  }

  return lightControllers;
}

LedLightPtr *createLights(int lightIds[]) {
  LedLightPtr *result = new LedLightPtr[NUMBER_OF_LIGHTS];

  for (int i = 0 ; i < NUMBER_OF_LIGHTS ; i++) {
    LedLightPtr light = new LedLight(lightIds[i]);

    result[i] = light;
  }

  return result;
}

void pollButtons(unsigned long currentTimeMs) {
  gradualButton->clockTick(currentTimeMs);
  offButton->clockTick(currentTimeMs);
}

void readButtons(StateMachine *stateMachine, unsigned long currentTimeMs ) {
  if (offButton->isPressed()) {
    stateMachine->switchOff();
  } else if (gradualButton->isPressed()) {
    stateMachine->switchGradual(currentTimeMs, 5000);
  }
}

void showStatus(State state) {
  if (state == StateOff) {
    statusLight->turnOff();
  } else {
    statusLight->turnOn();
  }
}
