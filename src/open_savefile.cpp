/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.3.0
 * See LICENSE.md file in the project root for full license information.
*/

#include <open_savefile.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <shlobj.h>
#include <windows.h>

using json = nlohmann::json;

std::string openSaveFile() {
  char appDataPath[MAX_PATH];
  SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
  std::string gameFolderPath = std::string(appDataPath) + "\\MathOrDeath";
  std::cout << appDataPath << std::endl << gameFolderPath << std::endl;

  // Create the directory if it doesn't already exist
  std::filesystem::create_directory(gameFolderPath);
  // Define the save file path
  std::string saveFilePath = gameFolderPath + "\\saveFile.json";

  // Formatted output string

  int highestHighScore = 0;
  
  // Create a JSON object to append
  json saveFileObject;
  std::ifstream saveFile(saveFilePath);
  saveFile >> saveFileObject;
  saveFile.close();

  for (const auto& item : saveFileObject) {
            if (item.contains("HighScore")) { // Check if "HighScore" exists
                int currentScore = item["HighScore"];
                if (currentScore > highestHighScore) {
                    highestHighScore = currentScore;
                }
            }
        }
  
  std::string highscore = std::to_string(highestHighScore);
  return highscore;
}
