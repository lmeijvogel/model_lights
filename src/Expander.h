#ifndef EXPANDER_H
#define EXPANDER_H

class Expander {
 public:
  Expander(int address);

  void send();
  void set(int bit);
  void clear(int bit);
private:
  int address;

  int sum = 0;
  int previousSum = 0;
};

#endif
