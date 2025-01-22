/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <iostream>
#include <sstream>
#include <string>

float getEquationAnswer(std::string originalEquation) {
  int num1, num2;
  char op;

  std::stringstream ss(originalEquation);

  ss >> num1;
  ss >> op;
  ss >> num2;

  float result;

  switch (op) {
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '*':
      result = num1 * num2;
      break;
    case '/':
      result = static_cast<float>(num1) / num2;  // Casting num1 to float
      break;
  }

  return result;
}
