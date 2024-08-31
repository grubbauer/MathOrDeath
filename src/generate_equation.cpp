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
