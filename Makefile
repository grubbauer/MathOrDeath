VERSION := v.0.0.1-16

CC := clang++
SOURCE := src/main.cpp src/random.cpp
RESOURCE_DIR := src\res
INCLUDE_DIR := include
LIB_DIR := lib
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer
BUILD_DIR := build\windows-x64

all: clean windows-x64

windows-x64:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) -mwindows $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
	copy "bin\*" $(BUILD_DIR)
	xcopy "src\res" "$(BUILD_DIR)\res" /E /I /H /C /Y
	del $(BUILD_DIR)\sdl2-config

clean:
	@if exist "$(BUILD_DIR)\.." rmdir /s /q "$(BUILD_DIR)\.."

debug: clean debug-1

debug-1: 
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
	copy "bin\*" $(BUILD_DIR)
	xcopy "src\res" "$(BUILD_DIR)\res" /E /I /H /C /Y
	del $(BUILD_DIR)\sdl2-config
	cd $(BUILD_DIR) && .\MathOrDeath_$(VERSION).exe
