/*
 * Copyright (C) 2024-2025 Raphael G. Grubbauer / GSP
 * This file is part of MathOrDeath and is subject to the terms of the End User
 * License Agreement (EULA).
 * Unauthorized use, modification, or distribution is prohibited.
 * See the EULA for details.
*/

#include <sstream>
#include <string>

#include "grubbauer/equation.h"
#include "grubbauer/random.h"

namespace grubbauer {
std::string getRandomEquation(int max) {
  char op;
  int rawOp = randomNum(1, 4);
  int num1 = randomNum(1, (max * 2));
  int num2 = randomNum(1, (max * 2));

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

  std::string equation =
    std::to_string(num1) + " " + op + " " + std::to_string(num2);

  return equation;
}

float getEquationAnswer(std::string equation) {
  int num1, num2;
  float answer = 0.0f;
  char op;

  std::stringstream ss(equation);

  ss >> num1;
  ss >> op;
  ss >> num2;

  switch (op) {
    case '+':
      answer = num1 + num2;
      break;
    case '-':
      answer = num1 - num2;
      break;
    case '*':
      answer = num1 * num2;
      break;
    case '/':
      answer = static_cast<float>(num1) / num2;
      break;
  }

  return answer;
}
}
