/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.3.0
 * See LICENSE.md file in the project root for full license information.
*/

#include "random.h"

int randNum(int min, int max) {
  std::random_device rd;  // Random device
  std::mt19937 gen(rd());  // Using the 32-bit Mersenne Twister Generator
  std::uniform_int_distribution<> distr(min, max);

  return distr(gen);
}

