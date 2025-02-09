/*
 * Copyright (c) Raphael Grubbauer 2024-2025
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
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
