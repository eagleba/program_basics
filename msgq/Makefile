# Message Queue Library Makefile
CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2

TARGET = ../lib/libmsgq.a
SOURCES = queue.c msgq_ipc.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)
	@echo "msgq library built: $(TARGET)"

$(TARGET): $(OBJECTS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-@del /Q *.o 2>nul
	-@del /Q $(TARGET) 2>nul
	@echo "msgq cleaned"

.PHONY: all clean
