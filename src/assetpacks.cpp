/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <shlobj.h>

#include <fstream>
#include <iostream>
#include <string>

#include "grubbauer/assetpacks.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace grubbauer {
bool checkForAssetPack() {
  // Get %APPDATA%
  char appDataPath[MAX_PATH];
  SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";

  // Checks if assetpack exists
  std::string assetpackFolder = gameFolderPath + "\\assetpack";
  std::ifstream file(assetpackFolder + "\\properties.json");
  if (file) {
    return true;
  } else {
    return false;
  }
}

std::string readAssetPackMetadata() {
  // Get %APPDATA%
  char appDataPath[MAX_PATH];
  SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";

  std::string assetpackFolder = gameFolderPath + "\\assetpack";

  // Create a JSON object
  json propertiesObject;
  std::ifstream propertiesFile(assetpackFolder + "\\properties.json");
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
}
