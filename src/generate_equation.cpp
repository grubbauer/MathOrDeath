/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.3.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <string>

#include "random.h"

std::string randEquation(int lvl) {
  int rawOp = randNum(1, 4);
  int firstNum = randNum(lvl, (lvl * 2));
  int secondNum = randNum(lvl, (lvl * 2));
  char op;

  switch (rawOp) {
    case 1:
      op = '+';
      break;
    case 2:
      op = '-';
      break;
    case 3:
      op = '*';
      break;
    case 4:
      op = '/';
      break;
  }

  return std::to_string(firstNum) + " " + op + " " + std::to_string(secondNum);
}

