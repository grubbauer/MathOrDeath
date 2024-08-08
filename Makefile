VERSION = v.0.0.1-11

CC := clang++.exe
C_CPP_FILES := src/main.cpp
RESOURCE_DIR := src/res
INCLUDE_DIR := include
LIBRARY_DIR := lib/x64
OUTPUT_DIR := build/windows-x64
OUTPUT_FILE := MathOrDeath_$(VERSION).exe
LIBRARIES := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lShell32

all:
	@if not exist "$(OUTPUT_DIR)" mkdir "$(OUTPUT_DIR)"
	$(CC) $(C_CPP_FILES) -o $(OUTPUT_DIR)/$(OUTPUT_FILE) -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) $(LIBRARIES) -Xlinker /SUBSYSTEM:WINDOWS -Xlinker /ENTRY:mainCRTStartup
	copy "$(LIBRARY_DIR)\*.dll" "$(OUTPUT_DIR)\"
	xcopy /e /y "$(RESOURCE_DIR)" "$(OUTPUT_DIR)\res\"

clean:
	rmdir /s /q build
