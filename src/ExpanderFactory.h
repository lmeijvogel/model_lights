#ifndef EXPANDER_FACTORY_H
#define EXPANDER_FACTORY_H

#include "ExpanderOutput.h"

// TODO: Delete unused
typedef ExpanderOutput* ExpanderOutputPtr;
typedef Expander* ExpanderPtr;
typedef Light* LightPtr;

class ExpanderFactory {
public:
  ExpanderFactory(int numberOfOutputs, int numberOfExpanders, int* expanderAddresses);

  void build(LightPtr* outputs, ExpanderPtr* expanders);

private:
  int numberOfOutputs;
  int numberOfExpanders;
  int *expanderAddresses;
};

#endif
