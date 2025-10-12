# Program Basics - Top Level Makefile

.DEFAULT_GOAL := all

all: lib test
	@echo "=== Build Complete ==="

lib:
	@echo "Building libraries..."
	@cd msgq && $(MAKE)

test: lib
	@echo "Building tests..."
	@cd test\client_server && $(MAKE)

run-test:
	@cd test\client_server && $(MAKE) run

clean:
	@echo "Cleaning all..."
	@cd msgq && $(MAKE) clean
	@cd test\client_server && $(MAKE) clean
	@echo "Clean complete"

help:
	@echo "Available targets:"
	@echo "  all       - Build libraries and tests"
	@echo "  lib       - Build libraries only"
	@echo "  test      - Build tests"
	@echo "  run-test  - Run tests"
	@echo "  clean     - Clean all"
	@echo "  help      - Show this help"

.PHONY: all lib test run-test clean help

