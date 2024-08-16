VERSION := v.0.0.1-15

CC := clang++
SOURCE := src/main.cpp src/random.cpp
RESOURCE_DIR := src\res
INCLUDE_DIR := include
LIB_DIR := lib
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer
BUILD_DIR := build\windows-x64

all:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
	robocopy "$(RESOURCE_DIR)" "$(BUILD_DIR)" /e
	robocopy "bin/*" "$(BUILD_DIR)" /e

clean:
	@if exist "$(BUILD_DIR)\.." cmd /C rmdir /S /Q "$(BUILD_DIR)\.."
