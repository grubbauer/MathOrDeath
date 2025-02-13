/*
 * Copyright (C) 2024-2025 Raphael G. Grubbauer / GSP
 * This file is part of MathOrDeath and is subject to the terms of the End User
 * License Agreement (EULA).
 * Unauthorized use, modification, or distribution is prohibited.
 * See the EULA for details.
*/

#include <shlobj.h>

#include <fstream>
#include <iostream>
#include <string>

#include "grubbauer/assetpacks.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace grubbauer {

std::string getAssetPackDirectory() {
  // Get %APPDATA%
  char appDataPath[MAX_PATH];
  SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";
  std::string assetPackFolder = gameFolderPath + "\\assetpack";

  return assetPackFolder;
}

std::string readAssetPackMetadata() {
  std::string assetPackFolder = getAssetPackDirectory();

  // Create a JSON object
  json propertiesObject;
  std::ifstream propertiesFile(assetPackFolder + "\\properties.json");
  propertiesFile >> propertiesObject;
  propertiesFile.close();

  // Access JSON data
  if (!propertiesObject.empty() && propertiesObject[0].contains("AssetPack")) {
    auto assetPack = propertiesObject[0]["AssetPack"];
    // Extract values
    std::string name = assetPack.value("Name", "Unknown");
    std::string description = assetPack.value("Description", "Unknown");
    std::string version = assetPack.value("Version", "Unknown");

    return "Name: " + name + "\n" + "Description: " + description + "\n" + "Version: " + version + "\n";
  } else {
    std::cerr << "Invalid JSON format!" << std::endl;
    return "Unkown";
  }
}
bool checkForAssetPack() {
  std::string assetPackFolder = getAssetPackDirectory();

  std::ifstream file(assetPackFolder + "\\properties.json");
  if (file) {
    return true;
  } else {
    return false;
  }
}
}
