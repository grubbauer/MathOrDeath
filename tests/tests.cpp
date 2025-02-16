/*
 * Name:        tests/tests.cpp
 * Purpose:     Unit testing source file
 * Author:      Raphael G. Grubbauer
 * Created:     08.02.2025
 * Copyright:   (c) 2025 Raphael G. Grubbauer / GSP
 * License:     MathOrDeath EULA
*/

#include <iostream>
#include <string>
#include <algorithm>

#include "grubbauer/assetpacks.h"
#include "grubbauer/random.h"
#include "grubbauer/equation.h"
#include "grubbauer/savefile.h"

void testAssetpacks();
void testRandom();
void testEquation();
void testSavefile();

int main(int argc, char* argv[]) {
    std::string modules[5] = {"ASSETPACKS", "RANDOM", "EQUATION", "SAVEFILE", "ALL"};
    std::string selectedModule;

    std::cout << "\n\n\n\n";
    std::cout << "UNIT TESTING\n";
    std::cout << "============\n";
    std::cout << "\n\n\n";

    std::cout << "Available Modules: \n";
    for (const auto& module : modules) {
        std::cout << module << " ";
    }
    std::cout << "\n-------------------\n";
    std::cout << "\n\n";

    std::cout << "What test shall be executed?: ";
    std::cin >> selectedModule;
    std::transform(selectedModule.begin(), selectedModule.end(), selectedModule.begin(), ::toupper); 

    if (selectedModule == "ASSETPACKS") {
      std::cout << "-------------------\n";
      std::cout << "Selected ASSETPACKS.\n\n";
      testAssetpacks();
    } else if(selectedModule == "RANDOM") {
      std::cout << "----------------\n";
      std::cout << "Selected RANDOM.\n\n";
      testRandom();
    } else if(selectedModule == "EQUATION") {
      std::cout << "------------------\n";
      std::cout << "Selected EQUATION.\n\n";
      testEquation();
    } else if(selectedModule == "SAVEFILE") {
      std::cout << "------------------\n";
      std::cout << "Selected SAVEFILE.\n\n";
      testSavefile();
    } else if(selectedModule == "ALL") {
      std::cout << "-------------\n";
      std::cout << "Selected ALL.\n\n";
      std::cout << "-------------------\n";
      std::cout << "Selected ASSETPACKS.\n\n";
      testAssetpacks();
      std::cout << "----------------\n";
      std::cout << "Selected RANDOM.\n\n";
      testRandom();
      std::cout << "------------------\n";
      std::cout << "Selected EQUATION.\n\n";
      testEquation();
      std::cout << "------------------\n";
      std::cout << "Selected SAVEFILE.\n\n";
      testSavefile();
    } else {
      std::cout << "No module with the name \"" << selectedModule <<"\"\n";
    }

    return 0;
}

void testAssetpacks() {
  std::cout << "Testing function \"checkForAssetPack\".\n";
  std::cout << grubbauer::checkForAssetPack() << "\n";

  std::cout << "Testing function \"getAssetPackDirectory\"\n";
  std::cout << grubbauer::getAssetPackDirectory() << "\n";

  std::cout << "Testing function \"readAssetPackMetadata\"\n";
  if (grubbauer::checkForAssetPack()) {
    std::cout << grubbauer::readAssetPackMetadata() << "\n";
  } else {
    std::cout << "0\n\n"; 
  }
}

void testRandom() {
  std::cout << "Testing function \"randomNum\".\n";
  std::cout << "Random number between 1 and 10: " << grubbauer::randomNum(1, 10) << "\n\n";
}

void testEquation() {
  std::cout << "Testing function \"getRandomEquation\".\n";
  std::string equation = grubbauer::getRandomEquation(10);
  std::cout << equation << "\n";

  std::cout << "Testing function \"getEquationAnswer\".\n";
  std::cout << grubbauer::getEquationAnswer(equation) << "\n\n";
}

void testSavefile() {
  std::cout << "Testing function \"saveSaveFile\".\n";
  grubbauer::saveSaveFile(42);

  std::cout << "Testing function \"readSaveFile\".\n";
  std::cout << grubbauer::readSaveFile() << "\n\n";
}
