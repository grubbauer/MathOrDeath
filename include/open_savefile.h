/*
 * Copyright (c) Raphael Grubbauer
 * Licensed under the Grubbauer Open Source License (GOSL) v1.3.0
 * See LICENSE.md file in the project root for full license information.
*/

#ifndef OPEN_SAVEFILE_H
#define OPEN_SAVEFILE_H

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

nlohmann::json openSaveFile();

#endif
