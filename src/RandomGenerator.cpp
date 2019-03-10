#include <math.h>
#include <stdlib.h>

#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int seed) {
  srand(seed);
}

int RandomGenerator::getNext(int max) {
  return max * rand();
}

float RandomGenerator::getNextPoisson(int rateParameter) {
  return -logf(1.0f - (float) rand() / (RAND_MAX)) / (float)rateParameter;
}
