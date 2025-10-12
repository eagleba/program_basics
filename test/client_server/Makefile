# Client-Server Test Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -pthread
INCLUDES = -I../../include
LDFLAGS = -L../../lib

SOURCES = test_client_server.c
TARGET_MSGQ = test_client_server_msgq.exe
TARGET_PIPE = test_client_server_pipe.exe

all: $(TARGET_MSGQ)
	@echo "Built client-server tests"

$(TARGET_MSGQ): $(SOURCES) ../../lib/libmsgq.a
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LDFLAGS) -lmsgq

$(TARGET_PIPE): $(SOURCES) ../../lib/libpipe.a
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LDFLAGS) -lpipe

clean:
	-@del /Q *.exe *.o 2>nul
	@echo "Cleaned"

run: $(TARGET_MSGQ)
	@echo.
	@.\$(TARGET_MSGQ)

.PHONY: all clean run

