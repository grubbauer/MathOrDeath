#include <string>

#include "random.h"

std::string randEquation(int lvl) {
  int rawOperator = randNum(1, 4);
  int firstNum = randNum(lvl, (lvl * 10));
  int secondNum = randNum(lvl, (lvl * 10));
  char Operator;

  switch (rawOperator) {
    case 1:
      Operator = '+';
      break;
    case 2:
      Operator = '-';
      break;
    case 3:
      Operator = '*';
      break;
    case 4:
      Operator = '/';
      break;
  }

  return std::to_string(firstNum) + " " + Operator + " " +
         std::to_string(secondNum);
}
