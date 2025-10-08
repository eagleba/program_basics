# Main Makefile for Message Queue Course
# This Makefile can build all projects from the msgq directory

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
DEBUG_CFLAGS = -Wall -Wextra -std=c99 -g -DDEBUG

# Directories
V1_DIR = v1
RESERVE_DIR = reserve

# Targets
V1_TARGET = $(V1_DIR)/demo.exe

# Default target - build v1
all: v1
	@echo "=== All projects built successfully! ==="

# Build v1 queue library
v1: $(V1_TARGET)
	@echo "Queue v1 built"

# Build queue v1 demo
$(V1_TARGET): $(V1_DIR)/queue.c $(V1_DIR)/demo.c
	@echo "Building queue v1 demo..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Queue v1 demo built: $@"

# Debug versions
debug: debug-v1
	@echo "=== All debug versions built! ==="

debug-v1: $(V1_DIR)/demo_debug.exe
	@echo "Debug v1 built"

$(V1_DIR)/demo_debug.exe: $(V1_DIR)/queue.c $(V1_DIR)/demo.c
	@echo "Building debug queue v1 demo..."
	$(CC) $(DEBUG_CFLAGS) -o $@ $^
	@echo "Debug queue v1 demo built: $@"

# Clean all compiled files
clean:
	@echo "Cleaning all compiled files..."
	del /Q $(V1_DIR)\*.exe 2>nul || echo "V1 cleaned"
	@echo "Clean completed"

# Run demos
run: run-v1

run-v1: $(V1_TARGET)
	@echo "=== Running Queue v1 Demo ==="
	$(V1_TARGET)

# Test projects
test: $(V1_TARGET)
	@echo "=== Testing Queue v1 Demo ==="
	$(V1_TARGET)
	@echo "=== Test completed ==="

# Show help
help:
	@echo "Message Queue Course - Available targets:"
	@echo ""
	@echo "  all          - Build all projects"
	@echo "  v1           - Build queue v1 library"
	@echo "  debug        - Build debug versions"
	@echo "  clean        - Clean all compiled files"
	@echo "  run          - Run demos"
	@echo "  test         - Test queue demo"
	@echo "  help         - Show this help"
	@echo ""
	@echo "Examples:"
	@echo "  mingw32-make all     # Build everything"
	@echo "  mingw32-make clean   # Clean all files"
	@echo "  mingw32-make test    # Test the queue demo"

.PHONY: all v1 debug debug-v1 clean run run-v1 test help