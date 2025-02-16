/*
 * Name:        include/grubbauer/savefile.h
 * Purpose:     SaveFile header
 * Author:      Raphael G. Grubbauer
 * Created:     07.02.2025
 * Copyright:   (c) 2025 Raphael G. Grubbauer / GSP
 * License:     MathOrDeath EULA
*/

#ifndef GRUBBAUER_SAVEFILE_H
#define GRUBBAUER_SAVEFILE_H

#include <string>

namespace grubbauer {
std::string readSaveFile();
void saveSaveFile(int lvl);
}

#endif
