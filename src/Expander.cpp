#include "Wire.h"

#include "Arduino.h"

#include "Expander.h"

Expander::Expander(int address) {
  Serial.print("Expander: Initialized with address ");
  Serial.println(address);
  this->address = address;
}

void Expander::set(int bit) {
  sum |= (1<<bit);
}

void Expander::clear(int bit) {
  int mask = 1<<bit;

  mask ^=0xff;

  sum &= mask;
}

void Expander::send() {
  if (sum != previousSum) {
    Serial.print("Sending new value: ");
    Serial.print(sum);
    Wire.beginTransmission(address);
    Wire.write(sum & 0xff);
    Wire.endTransmission();

    Serial.println("... done");

    previousSum = sum;
  }
}
