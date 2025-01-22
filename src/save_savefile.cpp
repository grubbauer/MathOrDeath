/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <save_savefile.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <shlobj.h>
#include <windows.h>

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

  // JSON object to hold the save data
  json saveFileObject = json::array();

  // Check if the file exists and is not empty
  std::ifstream saveFileIn(saveFilePath, std::ios::in);
  if (saveFileIn.is_open()) {
    saveFileIn.seekg(0, std::ios::end);
    if (saveFileIn.tellg() > 0) {  // Check if filesize is larger than 0
      saveFileIn.seekg(0, std::ios::beg);
      saveFileIn >> saveFileObject;
    }
    saveFileIn.close();
  }

  // Add the new level to the array
  saveFileObject.push_back({{"Level:", lvl--}});

  // Write the updated array back to the file
  std::ofstream saveFileOut(saveFilePath,
                            std::ios::trunc);  // Overwrite the file

  saveFileOut << saveFileObject.dump(2) << std::endl;
  saveFileOut.close();
}
