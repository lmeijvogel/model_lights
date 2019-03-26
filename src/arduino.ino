// the setup function runs once when you press reset or power the board
#include "LightCollectionController.h"
#include "LightController.h"
#include "ExpanderFactory.h"
#include "LedLight.h"
#include "StateMachine.h"
#include "StatusLedController.h"
#include "RandomGenerator.h"
#include "PhysicalButton.h"
#include "CircularActivator.h"

#include "Wire.h"

const int NUMBER_OF_EXPANDERS = 8;
int EXPANDER_ADDRESSES[] = { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27 };

const int LED_PINS[] = { 8, 9, 10, 11 };
typedef LightController* LightControllerPtr;
typedef Light* LightPtr;

const int NUMBER_OF_LIGHTS = 64;
const int NUMBER_OF_LEDS = 4;

const int TOTAL_NUMBER_OF_LIGHTS = NUMBER_OF_LIGHTS + NUMBER_OF_LEDS;

const int NUMBER_OF_BUTTONS = 2;

unsigned long startTime;

LightControllerPtr *createLightControllers(LightPtr *lights, int count, RandomGenerator *randomGenerator);

void pollButtons();
void readButtons(StateMachine *stateMachine, unsigned long currentTimeMs);
void showStatus(State state);

LightCollectionController *lightCollectionController;
StateMachine *stateMachine;

PhysicalButton *gradualButton;
PhysicalButton *offButton;

ExpanderPtr *expanders;

LedLight *statusLight;

LedLight *statusOnLight, *statusOffLight, *statusGradualLight;

CircularActivator *circularActivator;

boolean previousOffButtonPressed = false;
boolean previousGradualButtonPressed = false;

StatusLedController *statusLedController;

void setup() {
  Serial.begin(9600);

  Serial.println("Started!");
  Wire.begin();

  statusLight = new LedLight(LED_BUILTIN);
  statusOnLight = new LedLight(LED_BUILTIN);
  statusGradualLight = new LedLight(LED_BUILTIN);
  statusOffLight = new LedLight(LED_BUILTIN);

  startTime = millis();

  RandomGenerator randomGenerator(startTime);

  int gradualButtonId = 2;
  int offButtonId = 3;

  gradualButton = new PhysicalButton(gradualButtonId);
  offButton = new PhysicalButton(offButtonId);

  LightPtr *lights = new LightPtr[TOTAL_NUMBER_OF_LIGHTS];
  expanders = new ExpanderPtr[NUMBER_OF_EXPANDERS];

  ExpanderFactory expanderFactory(NUMBER_OF_LIGHTS, NUMBER_OF_EXPANDERS, EXPANDER_ADDRESSES);
  expanderFactory.build((LightPtr *)lights, expanders);

  for (int i = 0 ; i < NUMBER_OF_LEDS ; i++) {
    lights[NUMBER_OF_LIGHTS + i] = new LedLight(LED_PINS[i]);
  }

  LightControllerPtr *lightControllers = createLightControllers((LightPtr *)lights, TOTAL_NUMBER_OF_LIGHTS, &randomGenerator);

  statusLedController = new StatusLedController(statusOffLight, statusGradualLight, statusOnLight);

  circularActivator = new CircularActivator((AbstractLightControllerPtr *)lightControllers, TOTAL_NUMBER_OF_LIGHTS, 5);

  lightCollectionController = new LightCollectionController(lightControllers, circularActivator, TOTAL_NUMBER_OF_LIGHTS);

  stateMachine = new StateMachine(lightCollectionController, statusLedController);
  stateMachine->switchGradual(millis(), 10000);
}

// the loop function runs over and over again forever
void loop() {
  unsigned long now = millis();

  pollButtons();
  readButtons(stateMachine, now);

  stateMachine->clockTick(now);

  showStatus(stateMachine->getState());

  lightCollectionController->clockTick(now);

  for (int i = 0 ; i < NUMBER_OF_EXPANDERS ; i++) {
    expanders[i]->send();
  }
}

LightControllerPtr *createLightControllers(LightPtr *lights, int count, RandomGenerator *randomGenerator) {
  LightControllerPtr *lightControllers = new LightControllerPtr[count];

  for (int i = 0 ; i < count ; i++) {
    LightController *lightController = new LightController(lights[i], randomGenerator, 5000, 3000);
    lightControllers[i] = lightController;
  }

  return lightControllers;
}

void pollButtons() {
  gradualButton->clockTick();
  offButton->clockTick();
}

void readButtons(StateMachine *stateMachine, unsigned long currentTimeMs ) {
  boolean offButtonPressed = offButton->isPressed();
  boolean gradualButtonPressed = gradualButton->isPressed();

  if (offButtonPressed && !previousOffButtonPressed) {
    stateMachine->switchOff();
  } else if (gradualButtonPressed && !previousGradualButtonPressed) {
    stateMachine->switchGradual(currentTimeMs, 5000);
  }

  previousOffButtonPressed = offButtonPressed;
  previousGradualButtonPressed = gradualButtonPressed;
}

void showStatus(State state) {
  if (state == StateOff) {
    statusLight->turnOff();
  } else {
    statusLight->turnOn();
  }
}
