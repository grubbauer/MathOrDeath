/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#include "grubbauer/equation.h"
#include "grubbauer/random.h"

#include <string>
#include <sstream>

namespace grubbauer {
  std::string getRandomEquation(int range) {
    char op;
    int rawOp = randomNum(1, 4);
    int num1 = randomNum(range, (range * 2));
    int num2 = randomNum(range, (range * 2));

    switch(rawOp) {
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

    std::string equation = std::to_string(num1) + " " + op + " " + std::to_string(num2);

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
