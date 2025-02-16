/*
 * Name:        include/grubbauer/equation.h
 * Purpose:     Equation generation and solving header
 * Author:      Raphael G. Grubbauer
 * Created:     07.02.2025
 * Copyright:   (c) 2025 Raphael G. Grubbauer / GSP
 * License:     MathOrDeath EULA
*/

#ifndef GRUBBAUER_EQUATION_H
#define GRUBBAUER_EQUATION_H

#include <string>

namespace grubbauer {
std::string getRandomEquation(int max);
float getEquationAnswer(std::string equation);
}

#endif
