# Queue v1 Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
DEBUG_CFLAGS = -Wall -Wextra -std=c99 -g -DDEBUG
TARGET = demo
SOURCES = queue.c demo.c

# Default target
all: $(TARGET)

# Compile target
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Debug version
debug: $(SOURCES)
	$(CC) $(DEBUG_CFLAGS) -o $(TARGET)_debug $(SOURCES)

# Clean
clean:
	del /Q $(TARGET).exe $(TARGET)_debug.exe 2>nul || echo "Clean completed"

# Run
run: $(TARGET)
	$(TARGET).exe

# Test
test: $(TARGET)
	$(TARGET).exe

# Help
help:
	@echo "Queue v1 - Available targets:"
	@echo ""
	@echo "  all     - Compile program"
	@echo "  debug   - Compile debug version"
	@echo "  clean   - Clean compiled files"
	@echo "  run     - Compile and run program"
	@echo "  test    - Test the queue demo"
	@echo "  help    - Show this help"
	@echo ""
	@echo "Examples:"
	@echo "  mingw32-make all     # Build program"
	@echo "  mingw32-make test    # Test the queue"

.PHONY: all debug clean run test help
