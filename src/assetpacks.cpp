/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <shlobj.h>

#include <fstream>
#include <string>

#include "grubbauer/assetpacks.h"

namespace grubbauer {
bool checkForAssetpacks() {
  char appDataPath[MAX_PATH];

  // Get %APPDATA%
  SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";

  // Checks if assetpack exists
  std::string assetpackFolder = gameFolderPath + "\\assetpack";
  std::ifstream file(assetpackFolder + "properties.json");
  if(file) {
    return true;
  } else {
    return false;
  }
}
}
