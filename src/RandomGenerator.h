#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

class RandomGenerator {
public:
  RandomGenerator(int seed);

  virtual int getNext(int max);
  virtual float getNextPoisson(int rateParameter);
};
#endif
