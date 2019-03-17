#ifndef DELAYABLE_H
#define DELAYABLE_H

class Delayable {
public:
  virtual void changeDelay(double factor) = 0;
};

#endif
