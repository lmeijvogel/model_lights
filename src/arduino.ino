// the setup function runs once when you press reset or power the board
#include "LightCollectionController.h"
#include "LightController.h"
#include "ExpanderOutput.h"
#include "Expander.h"
#include "LedLight.h"
#include "StateMachine.h"
#include "RandomGenerator.h"
#include "PhysicalButton.h"
#include "CircularActivator.h"

#include "Wire.h"

#define PCF8574_ADDR (0x20)

typedef LightController* LightControllerPtr;
typedef Light* LightPtr;
typedef ExpanderOutput* ExpanderOutputPtr;

const int NUMBER_OF_LIGHTS = 8;
const int NUMBER_OF_BUTTONS = 2;

unsigned long startTime;

LightControllerPtr *createLightControllers(LightPtr *lights, int count, RandomGenerator *randomGenerator);
ExpanderOutputPtr *createLights(Expander *expander, int numberOfLights);

void pollButtons(unsigned long currentTimeMs);
void readButtons(StateMachine *stateMachine, unsigned long currentTimeMs);
void showStatus(State state);

LightCollectionController *lightCollectionController;
StateMachine *stateMachine;

PhysicalButton *gradualButton;
PhysicalButton *offButton;

LedLight *statusLight;

CircularActivator *circularActivator;

Expander *expander;

void setup() {
  Wire.begin();

  statusLight = new LedLight(LED_BUILTIN);

  startTime = millis();

  RandomGenerator randomGenerator(startTime);

  int gradualButtonId = 2;
  int offButtonId = 3;

  gradualButton = new PhysicalButton(gradualButtonId);
  offButton = new PhysicalButton(offButtonId);

  expander = new Expander(PCF8574_ADDR);
  ExpanderOutputPtr *lights = createLights(expander, NUMBER_OF_LIGHTS);

  LightControllerPtr *lightControllers = createLightControllers((LightPtr *)lights, NUMBER_OF_LIGHTS, &randomGenerator);

  circularActivator = new CircularActivator((AbstractLightControllerPtr *)lightControllers, NUMBER_OF_LIGHTS, 5);

  lightCollectionController = new LightCollectionController(lightControllers, circularActivator, NUMBER_OF_LIGHTS);

  stateMachine = new StateMachine(lightCollectionController);
  stateMachine->switchGradual(millis(), 10000);
}

// the loop function runs over and over again forever
void loop() {
  unsigned long now = millis();

  pollButtons(now);
  readButtons(stateMachine, now);

  stateMachine->clockTick(now);

  showStatus(stateMachine->getState());

  lightCollectionController->clockTick(now);

  expander->send();
}

LightControllerPtr *createLightControllers(LightPtr *lights, int count, RandomGenerator *randomGenerator) {
  LightControllerPtr *lightControllers = new LightControllerPtr[count];

  for (int i = 0 ; i < count ; i++) {
    LightController *lightController = new LightController(lights[i], randomGenerator, 5000, 3000);
    lightControllers[i] = lightController;
  }

  return lightControllers;
}

ExpanderOutputPtr *createLights(Expander *expander, int numberOfLights) {
  ExpanderOutputPtr *result = new ExpanderOutputPtr[numberOfLights];

  for (int i = 0 ; i < numberOfLights ; i++) {
    ExpanderOutputPtr light = new ExpanderOutput(expander, i);

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
