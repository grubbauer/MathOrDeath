/*
 * Copyright (C) 2024-2025 Raphael G. Grubbauer / GSP
 * This file is part of MathOrDeath and is subject to the terms of the End User
 * License Agreement (EULA).
 * Unauthorized use, modification, or distribution is prohibited.
 * See the EULA for details.
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
