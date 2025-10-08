# Main Makefile for Message Queue Course
# This Makefile can build all examples from the msgq directory

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
DEBUG_CFLAGS = -Wall -Wextra -std=c99 -g -DDEBUG

# Directories
EXAMPLES_DIR = examples
PRINCIPLES_DIR = $(EXAMPLES_DIR)/02-principles
PRACTICE_DIR = $(EXAMPLES_DIR)/03-practice

# Targets
PRINCIPLES_TARGET = $(PRINCIPLES_DIR)/queue_demo.exe
PRACTICE_TARGETS = $(PRACTICE_DIR)/sensor_demo/simple_demo.exe

# Default target - build everything
all: principles practice
	@echo "=== All projects built successfully! ==="

# Build principles examples
principles: $(PRINCIPLES_TARGET)
	@echo "Principles examples built"

# Build practice examples  
practice: $(PRACTICE_TARGETS)
	@echo "Practice examples built"

# Build simple queue demo
$(PRINCIPLES_TARGET): $(PRINCIPLES_DIR)/simple_queue.c $(PRINCIPLES_DIR)/queue_demo.c
	@echo "Building simple queue demo..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Simple queue demo built: $@"

# Build sensor demo (simplified version)
$(PRACTICE_DIR)/sensor_demo/simple_demo.exe: $(PRACTICE_DIR)/sensor_demo/simple_windows_demo.c
	@echo "Building sensor demo..."
	$(CC) $(CFLAGS) -o $@ $<
	@echo "Sensor demo built: $@"

# Debug versions
debug: debug-principles debug-practice
	@echo "=== All debug versions built! ==="

debug-principles: $(PRINCIPLES_DIR)/queue_demo_debug.exe
	@echo "Debug principles examples built"

$(PRINCIPLES_DIR)/queue_demo_debug.exe: $(PRINCIPLES_DIR)/simple_queue.c $(PRINCIPLES_DIR)/queue_demo.c
	@echo "Building debug simple queue demo..."
	$(CC) $(DEBUG_CFLAGS) -o $@ $^
	@echo "Debug simple queue demo built: $@"

# Clean all compiled files
clean:
	@echo "Cleaning all compiled files..."
	del /Q $(PRINCIPLES_DIR)\*.exe 2>nul || echo "Principles cleaned"
	del /Q $(PRACTICE_DIR)\sensor_demo\*.exe 2>nul || echo "Practice cleaned"
	del /Q $(PRACTICE_DIR)\sensor_demo\message_queue.dat 2>nul || echo "Data files cleaned"
	@echo "Clean completed"

# Run all demos
run: run-principles run-practice

run-principles: $(PRINCIPLES_TARGET)
	@echo "=== Running Simple Queue Demo ==="
	$(PRINCIPLES_TARGET)

run-practice: $(PRACTICE_DIR)/sensor_demo/simple_demo.exe
	@echo "=== Running Sensor Demo ==="
	@echo "Note: Run 'simple_demo.exe consumer' in one terminal"
	@echo "      Run 'simple_demo.exe producer' in another terminal"
	$(PRACTICE_DIR)/sensor_demo/simple_demo.exe consumer

# Test all projects
test: $(PRINCIPLES_TARGET)
	@echo "=== Testing Simple Queue Demo ==="
	$(PRINCIPLES_TARGET)
	@echo "=== Test completed ==="

# Show help
help:
	@echo "Message Queue Course - Available targets:"
	@echo ""
	@echo "  all          - Build all projects"
	@echo "  principles   - Build principles examples only"
	@echo "  practice     - Build practice examples only"
	@echo "  debug        - Build debug versions of all projects"
	@echo "  clean        - Clean all compiled files"
	@echo "  run          - Run all demos"
	@echo "  run-principles - Run simple queue demo"
	@echo "  run-practice   - Run sensor demo (consumer mode)"
	@echo "  test         - Test simple queue demo"
	@echo "  help         - Show this help"
	@echo ""
	@echo "Examples:"
	@echo "  mingw32-make all     # Build everything"
	@echo "  mingw32-make clean   # Clean all files"
	@echo "  mingw32-make test    # Test the queue demo"

# Mark targets as phony
.PHONY: all principles practice debug debug-principles clean run run-principles run-practice test help
