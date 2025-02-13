/*
 * Copyright (C) 2024-2025 Raphael G. Grubbauer / GSP
 * This file is part of MathOrDeath and is subject to the terms of the End User
 * License Agreement (EULA).
 * Unauthorized use, modification, or distribution is prohibited.
 * See the EULA for details.
*/

#ifndef GRUBBAUER_ASSETSPACK_H
#define GRUBBAUER_ASSETSPACK_H

#include <string>

namespace grubbauer {
std::string getAssetPackDirectory();
std::string readAssetPackMetadata();
bool checkForAssetPack();
}

#endif
