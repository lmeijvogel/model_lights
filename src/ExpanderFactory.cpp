#include <math.h>

#include "ExpanderFactory.h"
#include "Expander.h"

#include "Arduino.h"

ExpanderFactory::ExpanderFactory(int numberOfOutputs, int numberOfExpanders, int* expanderAddresses) {
  this->numberOfOutputs = numberOfOutputs;
  this->numberOfExpanders = numberOfExpanders;
  this->expanderAddresses = expanderAddresses;
}

void ExpanderFactory::build(LightPtr* outputs, ExpanderPtr* expanders) {
  int positionInOutput = 0;

  for (int expanderIndex = 0 ; expanderIndex < numberOfExpanders ; expanderIndex++) {
    int expanderAddress = expanderAddresses[expanderIndex];

    int portOnExpander = 0;

    Expander *expander = new Expander(expanderAddress);
    expanders[expanderIndex] = expander;

    while (portOnExpander < 8 && positionInOutput < numberOfOutputs) {
      ExpanderOutput *expanderOutput = new ExpanderOutput(expander, portOnExpander);

      Serial.print("Creating output, Expander: ");
      Serial.print(expanderIndex);
      Serial.print(", output: ");
      Serial.println(portOnExpander);
      outputs[positionInOutput] = expanderOutput;

      positionInOutput++;
      portOnExpander++;
    }
  }
}
