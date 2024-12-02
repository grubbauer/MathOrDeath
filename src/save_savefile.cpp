/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.3.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <save_savefile.h>

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <shlobj.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void saveSaveFile(int lvl) {
  char appDataPath[MAX_PATH];
  SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";
  std::cout << appDataPath << std::endl << gameFolderPath << std::endl;

  // Create the directory if it doesn't already exist
  std::filesystem::create_directory(gameFolderPath);

  // Define the save file path
  std::string saveFilePath = gameFolderPath + "\\saveFile.json";

  // Create a JSON object to append
  json saveFileObject = {
    {"Level:", lvl--}
  };

  // Open the file in append mode
  std::ofstream saveFile(saveFilePath, std::ios::app);
  
  if (!saveFile) {
    std::cerr << "Failed to open the save file for appending." << std::endl;
    return;
  }

  // Append the JSON data to the file
  saveFile << saveFileObject.dump(2) << std::endl;

  saveFile.close();
}

