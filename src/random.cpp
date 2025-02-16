/*
 * Name:        src/random.cpp
 * Purpose:     Random number generation logic
 * Author:      Raphael G. Grubbauer
 * Created:     13.08.2024
 * Copyright:   (c) 2024 Raphael G. Grubbauer / GSP
 * License:     MathOrDeath EULA
*/

#include <random>

#include "grubbauer/random.h"

namespace grubbauer {
int randomNum(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());  // Using 32-bit Mersenne Twister
  std::uniform_int_distribution<> distr(min, max);

  return distr(gen);
}
}
