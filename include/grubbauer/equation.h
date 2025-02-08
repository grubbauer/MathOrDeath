/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#ifndef GRUBBAUER_EQUATION_H
#define GRUBBAUER_EQUATION_H

#include <string>

namespace grubbauer {
std::string getRandomEquation(int max);
float getEquationAnswer(std::string equation);
}

#endif
