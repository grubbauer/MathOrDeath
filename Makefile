VERSION := v0.5.0-alpha

CC := clang++
SOURCE := src/main.cpp src/random.cpp src/generate_equation.cpp src/equation_answer.cpp
RESOURCE_DIR := src\res
BUILD_RES_DIR := res
INCLUDE_DIR := include
LIB_DIR := lib
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
BIN_DIR := bin
BUILD_DIR := build\windows-x64

all: clean windows-x64
debug: clean debug-1

windows-x64:
	@echo Creating build directory...
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@echo Sucess.
	@echo Building main executable...
	$(CC) -mwindows $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
	@echo Sucess
	@echo Copying resource files
	copy "$(BIN_DIR)\*" $(BUILD_DIR)
	xcopy "$(RESOURCE_DIR)" "$(BUILD_DIR)\$(BUILD_RES_DIR)" /E /I /H /C /Y
	del $(BUILD_DIR)\sdl2-config
	@echo Sucess.
	@echo Build complete.

clean:
	@echo Starting clean process...
	@if exist "$(BUILD_DIR)\.." rmdir /s /q "$(BUILD_DIR)\.."
	@echo Sucess.

debug-1: 
	@echo Creating build directory...
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@echo Sucess.
	@echo Building main executable...
	$(CC) $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS) -v
	@echo Sucess
	@echo Copying resource files
	copy "$(BIN_DIR)\*" $(BUILD_DIR)
	xcopy "$(RESOURCE_DIR)" "$(BUILD_DIR)\$(BUILD_RES_DIR)" /E /I /H /C /Y
	del $(BUILD_DIR)\sdl2-config
	@echo Sucess.
	@echo Build complete.
	@echo Now launching executable
	cd $(BUILD_DIR) && .\MathOrDeath_$(VERSION).exe
