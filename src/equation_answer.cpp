#include <iostream>
#include <sstream>
#include <string>

int getEquationAnswer(std::string originalEquation) {
  int num1, num2;
  char op;

  std::stringstream ss(originalEquation);

  ss >> num1;
  ss >> op;
  ss >> num2;

  int result;

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
      result = num1 / num2;
      break;
  }

  return result;
}