/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.3.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <open_savefile.h>

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <shlobj.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json openSaveFile() {
  char appDataPath[MAX_PATH];
  SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";
  std::cout << appDataPath << std::endl << gameFolderPath << std::endl;

  // Create the directory if it doesn't already exist
  std::filesystem::create_directory(gameFolderPath);
  // Define the save file path
  std::string saveFilePath = gameFolderPath + "\\saveFile.json";

  // Create a JSON object to append
  json saveFileObject;
  std::ifstream saveFile(saveFilePath);
  saveFile >> saveFileObject;

  saveFile.close();
  return saveFileObject;
}

