/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.3.0
 * See LICENSE.md file in the project root for full license information.
*/

#ifndef SAVE_SAVEFILE_H
#define SAVE_SAVEFILE_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <windows.h>

void saveSaveFile(int lvl);

#endif