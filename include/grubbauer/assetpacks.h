/*
 * Name:        include/grubbauer/assetpacks.h
 * Purpose:     AssetPacks header
 * Author:      Raphael G. Grubbauer
 * Created:     07.02.2025
 * Copyright:   (c) 2025 Raphael G. Grubbauer / GSP
 * License:     MathOrDeath EULA
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
