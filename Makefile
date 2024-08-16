VERSION := v.0.0.1-14

CC := clang++
SOURCE := src/main.cpp src/random.cpp
RESOURCE_DIR := src\res
INCLUDE_DIR := include
LIB_DIR := lib
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer
BUILD_DIR := build\windows-x64

all: windows-x64

windows-x64:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	$(CC) -mwindows $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
	copy "bin\*" $(BUILD_DIR)
	xcopy "src\res" "$(BUILD_DIR)\res" /E /I /H /C /Y
	del $(BUILD_DIR)\sdl2-config

clean:
	rmdir build /s /q
