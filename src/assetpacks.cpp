/*
 * Name:        src/assetpacks.cpp
 * Purpose:     AssetPack logic implementation
 * Author:      Raphael G. Grubbauer
 * Created:     07.02.2025
 * Copyright:   (c) 2025 Raphael G. Grubbauer / GSP
 * License:     MathOrDeath EULA
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

    return "Name: " + name + "\n" + "Description: " + description + "\n" +
           "Version: " + version + "\n";
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
