/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#ifndef GRUBBAUER_ASSETSPACK_H
#define GRUBBAUER_ASSETSPACK_H

#include <string>

namespace grubbauer {
bool checkForAssetPack();
std::string readAssetPackMetadata();
}

#endif
