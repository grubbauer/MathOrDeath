# Copyright (c) Raphael Grubbauer
# Licensed under the Grubbauer Open Source License (GOSL) v1.4.0
# See LICENSE.md file in the project root for full license information.

VERSION := v1.3.3

# Compiler and Directories
CC := clang++
STD := c++17
SOURCE := src/main.cpp
MODULES := src/random.cpp src/equation.cpp src/savefile.cpp src/assetpacks.cpp
TEST_SOURCE := tests/tests.cpp
INSTALLER_SOURCE := src/installer.cpp
RESOURCE_DIR := src\res
BUILD_RES_DIR := res
INCLUDE_DIR := include
LIB_DIR := lib
MINGW_BIN_DIR := C:\msys64\mingw64\bin
BIN_DIR := bin
BUILD_DIR := build\windows-x64
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
WXLIBS := -mwindows -lwxmsw32u -lwxmsw32u_gl -lwxscintilla -lwxregexu -lwxjpeg -lwxpng -lwxexpat -lwxtiff -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lole32 -loleaut32 -luuid -lcomctl32 -ladvapi32 -lcomctl32 -lshlwapi -luxtheme -lversion -lwxzlib -loleacc

# Targets
all: clean windows-x64 test
debug: clean debug-build
test: clean test-build
installer: installer-build

# Windows x64 Build
windows-x64: setup-build-dir
	@echo Building main executable...
	$(CC) -std=$(STD) -mwindows $(SOURCE) $(MODULES) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
	@echo Success.
	$(MAKE) copy-resources

# Debug Build
debug-build: setup-build-dir
	@echo Building main executable with debug information...
	$(CC) -std=$(STD) $(SOURCE) $(MODULES) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS) -v
	@echo Success.
	$(MAKE) copy-resources
	@echo Launching executable...
	cd $(BUILD_DIR) && .\MathOrDeath_$(VERSION).exe

# Test build
test-build:
	@echo "Building main executable"
	$(CC) $(TEST_SOURCE) $(MODULES) -o "tests\MathOrDeath_TESTS_$(VERSION).exe" -I$(INCLUDE_DIR)  -v

# Setup Build Directory
setup-build-dir:
	@echo Creating build directory...
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@echo Success.

# Copy Resources
copy-resources:
	@echo Copying resource files...
	copy "$(BIN_DIR)\*" "$(BUILD_DIR)"
	xcopy "$(RESOURCE_DIR)" "$(BUILD_DIR)\$(BUILD_RES_DIR)" /E /I /H /C /Y
	xcopy "$(MINGW_BIN_DIR)\libgcc_s_seh-1.dll" "$(BUILD_DIR)"
	xcopy "$(MINGW_BIN_DIR)\libwinpthread-1.dll" "$(BUILD_DIR)"
	xcopy "$(MINGW_BIN_DIR)\libstdc++-6.dll" "$(BUILD_DIR)"

	del "$(BUILD_DIR)\res\font\GPixel\*" /q
	del "$(BUILD_DIR)\res\font\GPixel-0001.*" /q
	del "$(BUILD_DIR)\res\font\GPixel.sfd" /q
	del "$(BUILD_DIR)\sdl2-config" /q
	@echo Success.

# Clean Build Directory
clean:
	@echo Starting clean process...
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@echo Success.

installer-build:
	@echo Starting installer build
	$(CC) -std=$(STD) -v -Wall $(INSTALLER_SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION)_INSTALLER.exe" -I$(INCLUDE_DIR) -L"D:\dev\lib\gcc_lib" $(WXLIBS)
	