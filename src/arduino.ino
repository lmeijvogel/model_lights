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

const int NUMBER_OF_LIGHTS = 16;
const int NUMBER_OF_EXPANDERS = 2;
int EXPANDER_ADDRESSES[] = { 0x20, 0x21 };

const int NUMBER_OF_LEDS = 0;
const int LED_PINS[] = { -1 };

const int STATUS_LED_ON_PIN = 8;
const int STATUS_LED_GRADUAL_PIN = 9;
const int STATUS_LED_OFF_PIN = 10;

typedef LightController* LightControllerPtr;
typedef Light* LightPtr;

const int TOTAL_NUMBER_OF_LIGHTS = NUMBER_OF_LIGHTS + NUMBER_OF_LEDS;

int ON_BUTTON_PIN = 2;
int GRADUAL_BUTTON_PIN = 3;
int OFF_BUTTON_PIN = 4;

const long GRADUAL_TRANSITION_PERIOD_MS = 60L*1000;

const long ON_TIME_DURATION = 120L*1000;
const long OFF_TIME_DURATION = 12L*1000;

unsigned long startTime;

LightControllerPtr *createLightControllers(LightPtr *lights, int count, RandomGenerator *randomGenerator);

void pollButtons();
void readButtons(StateMachine *stateMachine, unsigned long currentTimeMs);
void showStatus(State state);

LightCollectionController *lightCollectionController;
StateMachine *stateMachine;

PhysicalButton *onButton;
PhysicalButton *gradualButton;
PhysicalButton *offButton;

ExpanderPtr *expanders;

LedLight *statusLight;

LedLight *statusOnLight, *statusOffLight, *statusGradualLight;

LightPtr *lights;
LightControllerPtr *lightControllers;

CircularActivator *circularActivator;

boolean previousOnButtonPressed = false;
boolean previousGradualButtonPressed = false;
boolean previousOffButtonPressed = false;

StatusLedController *statusLedController;

void setup() {
  Serial.begin(9600);

  Serial.println("Started!");
  Wire.begin();

  statusLight = new LedLight(LED_BUILTIN);
  statusOnLight = new LedLight(STATUS_LED_ON_PIN);
  statusGradualLight = new LedLight(STATUS_LED_GRADUAL_PIN);
  statusOffLight = new LedLight(STATUS_LED_OFF_PIN);

  startTime = millis();

  RandomGenerator randomGenerator(startTime);

  onButton = new PhysicalButton(ON_BUTTON_PIN);
  gradualButton = new PhysicalButton(GRADUAL_BUTTON_PIN);
  offButton = new PhysicalButton(OFF_BUTTON_PIN);

  lights = new LightPtr[TOTAL_NUMBER_OF_LIGHTS];
  expanders = new ExpanderPtr[NUMBER_OF_EXPANDERS];

  ExpanderFactory expanderFactory(NUMBER_OF_LIGHTS, NUMBER_OF_EXPANDERS, EXPANDER_ADDRESSES);
  expanderFactory.build((LightPtr *)lights, expanders);

  for (int i = 0 ; i < NUMBER_OF_LEDS ; i++) {
    lights[NUMBER_OF_LIGHTS + i] = new LedLight(LED_PINS[i]);
  }

  lightControllers = createLightControllers((LightPtr *)lights, TOTAL_NUMBER_OF_LIGHTS, &randomGenerator);

  circularActivator = new CircularActivator((AbstractLightControllerPtr *)lightControllers, TOTAL_NUMBER_OF_LIGHTS, 5);

  lightCollectionController = new LightCollectionController(lightControllers, circularActivator, TOTAL_NUMBER_OF_LIGHTS);

  statusLedController = new StatusLedController(statusOffLight, statusGradualLight, statusOnLight);

  stateMachine = new StateMachine(lightCollectionController, statusLedController);
  stateMachine->switchGradual(millis(), GRADUAL_TRANSITION_PERIOD_MS);
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
  onButton->clockTick();
  gradualButton->clockTick();
  offButton->clockTick();
}

void readButtons(StateMachine *stateMachine, unsigned long currentTimeMs ) {
  boolean offButtonPressed = offButton->isPressed();
  boolean gradualButtonPressed = gradualButton->isPressed();
  boolean onButtonPressed = onButton->isPressed();

  if (offButtonPressed && !previousOffButtonPressed) {
    stateMachine->switchOff();
  } else if (gradualButtonPressed && !previousGradualButtonPressed) {
    stateMachine->switchGradual(currentTimeMs, GRADUAL_TRANSITION_PERIOD_MS);
  } else if (onButtonPressed && !previousOnButtonPressed) {
    stateMachine->switchOn();
  }

  previousOffButtonPressed = offButtonPressed;
  previousGradualButtonPressed = gradualButtonPressed;
  previousOnButtonPressed = onButtonPressed;
}

void showStatus(State state) {
  statusLedController->setState(state);

  if (state == StateOff) {
    statusLight->turnOff();
  } else {
    statusLight->turnOn();
  }
}
