# Currently, this makefile only supports windows clang builds
# But in the near future it will support gcc linux builds

# Variables
CXX := "clang-cl.exe"
INCLUDE_DIR := $(workspaceFolder)/include
OUTPUT_DIR := $(workspaceFolder)/build
OUTPUT_FILE := MathOrDeath_v_0_0_1-7.exe
LIB_DIR := $(workspaceFolder)/lib
LIBS := SDL2.lib SDL2main.lib SDL2_image.lib SDL2_mixer.lib kernel32.lib user32.lib gdi32.lib winmm.lib imm32.lib ole32.lib oleaut32.lib version.lib uuid.lib comdlg32.lib advapi32.lib shell32.lib

# Build rule
all: $(OUTPUT_DIR)/$(OUTPUT_FILE)

$(OUTPUT_DIR)/$(OUTPUT_FILE): $(file)
	$(CXX) -I$(INCLUDE_DIR) $(file) -o $(OUTPUT_DIR)/$(OUTPUT_FILE) -g -fcolor-diagnostics -fansi-escape-codes /link /LIBPATH:$(LIB_DIR) $(LIBS) /SUBSYSTEM:WINDOWS

# Clean rules
clean:
	del /Q $(OUTPUT_DIR)\$(OUTPUT_FILE)