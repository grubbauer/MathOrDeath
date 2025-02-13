/*
 * Copyright (C) 2024-2025 Raphael G. Grubbauer / GSP
 * This file is part of MathOrDeath and is subject to the terms of the End User
 * License Agreement (EULA).
 * Unauthorized use, modification, or distribution is prohibited.
 * See the EULA for details.
*/

#include <shlobj.h>
#include <windows.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "grubbauer/savefile.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace grubbauer {
std::string readSaveFile() {
  char appDataPath[MAX_PATH];
  int highestHighScore = 0;

  // Get %APPDATA%
  SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";

  std::filesystem::create_directory(gameFolderPath);
  std::string saveFilePath = gameFolderPath + "\\saveFile.json";

  // Create a JSON object
  json saveFileObject;
  std::ifstream saveFile(saveFilePath);
  saveFile >> saveFileObject;
  saveFile.close();

  // Loops over JSON object and tries to find the highest score
  for (const auto &item : saveFileObject) {
    if (item.contains("Level")) {  // Check if "Level" exists
      int currentScore = item["Level"];
      if (currentScore > highestHighScore) {
        highestHighScore = currentScore;
      }
    }
  }

  std::string highscore = std::to_string(highestHighScore);
  return highscore;
}

void saveSaveFile(int lvl) {
  char appDataPath[MAX_PATH];

  // Get %APPDATA%
  SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";

  std::filesystem::create_directory(gameFolderPath);
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

  saveFileObject.push_back({{"Level", lvl--}});

  // Overwrite object and save file
  std::ofstream saveFileOut(saveFilePath, std::ios::trunc);
  saveFileOut << saveFileObject.dump(2) << std::endl;
  saveFileOut.close();
}
}
