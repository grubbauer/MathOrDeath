VERSION := v0.7.0-alpha

# Compiler and Directories
CC := clang++
SOURCE := src/main.cpp src/random.cpp src/generate_equation.cpp src/equation_answer.cpp
RESOURCE_DIR := src\res
BUILD_RES_DIR := res
INCLUDE_DIR := include
LIB_DIR := lib
BIN_DIR := bin
BUILD_DIR := build\windows-x64

# Libraries
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Targets
all: clean windows-x64
debug: clean debug-build

# Windows x64 Build
windows-x64: setup-build-dir
	@echo Building main executable...
	$(CC) -mwindows $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS)
	@echo Success.
	$(MAKE) copy-resources

# Debug Build
debug-build: setup-build-dir
	@echo Building main executable with debug information...
	$(CC) $(SOURCE) -o "$(BUILD_DIR)\MathOrDeath_$(VERSION).exe" -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS) -v
	@echo Success.
	$(MAKE) copy-resources
	@echo Launching executable...
	cd $(BUILD_DIR) && .\MathOrDeath_$(VERSION).exe

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
	del "$(BUILD_DIR)\sdl2-config"
	@echo Success.

# Clean Build Directory
clean:
	@echo Starting clean process...
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@echo Success.
