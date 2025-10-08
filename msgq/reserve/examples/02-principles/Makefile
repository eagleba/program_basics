# Simple Queue Demo Program Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = queue_demo
SOURCES = simple_queue.c queue_demo.c

# Default target
all: $(TARGET)

# Compile target
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Clean
clean:
	del /Q $(TARGET).exe 2>nul || echo "Clean completed"

# Run
run: $(TARGET)
	$(TARGET).exe

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Compile program"
	@echo "  clean   - Clean compiled files"
	@echo "  run     - Compile and run program"
	@echo "  help    - Show this help information"

.PHONY: all clean run help
