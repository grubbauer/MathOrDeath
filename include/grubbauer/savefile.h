/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#ifndef GRUBBAUER_SAVEFILE_H
#define GRUBBAUER_SAVEFILE_H

#include <string>

namespace grubbauer {
  std::string readSaveFile();
  void saveSaveFile(int lvl);
}

#endif
