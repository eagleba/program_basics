# ============================================
# Queue v1 Makefile
# ============================================

# ========== 编译器配置 ==========
CC = gcc
AR = ar
STRIP = strip

# ========== 编译选项 ==========
# 基本编译标志
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
# 优化选项
OPT_FLAGS = -O2 -march=native
# 调试选项
DEBUG_FLAGS = -g -O0 -DDEBUG -fsanitize=address -fsanitize=undefined
# 包含路径
INCLUDES = -I.
# 链接选项
LDFLAGS = 
LDLIBS = 

# ========== 目标文件 ==========
TARGET = demo
TARGET_DEBUG = demo_debug
LIBRARY_STATIC = libqueue.a

# ========== 源文件 ==========
SOURCES = queue.c demo.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS_DEBUG = $(SOURCES:.c=_debug.o)

# 库文件源码
LIB_SOURCES = queue.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

# 依赖文件
DEPS = $(SOURCES:.c=.d)

# ========== 检测操作系统 ==========
ifeq ($(OS),Windows_NT)
    RM = del /Q
    RM_DIR = rmdir /S /Q
    EXE_EXT = .exe
    NULL_DEV = nul
else
    RM = rm -f
    RM_DIR = rm -rf
    EXE_EXT = 
    NULL_DEV = /dev/null
endif

# ========== 默认目标 ==========
.DEFAULT_GOAL := all

# ========== 主要构建目标 ==========

# Release 构建
all: $(TARGET)$(EXE_EXT)
	@echo.
	@echo "=== Build Complete ==="
	@echo "Executable: $(TARGET)$(EXE_EXT)"
	@echo.

# 链接可执行文件
$(TARGET)$(EXE_EXT): $(OBJECTS)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# 编译对象文件（包含依赖生成）
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# ========== Debug 构建 ==========
debug: $(TARGET_DEBUG)$(EXE_EXT)
	@echo.
	@echo "=== Debug Build Complete ==="
	@echo "Executable: $(TARGET_DEBUG)$(EXE_EXT)"
	@echo "Note: Built with AddressSanitizer and UndefinedBehaviorSanitizer"
	@echo.

# 链接调试版本
$(TARGET_DEBUG)$(EXE_EXT): $(OBJECTS_DEBUG)
	@echo "Linking debug version..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# 编译调试对象文件
%_debug.o: %.c
	@echo "Compiling $< (debug)..."
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# ========== 静态库构建 ==========
lib: $(LIBRARY_STATIC)
	@echo.
	@echo "=== Library Build Complete ==="
	@echo "Library: $(LIBRARY_STATIC)"
	@echo.

$(LIBRARY_STATIC): $(LIB_OBJECTS)
	@echo "Creating static library $@..."
	$(AR) rcs $@ $^

# ========== Release 优化版本 ==========
release: CFLAGS += -DNDEBUG
release: OPT_FLAGS = -O3 -march=native -flto
release: $(TARGET)$(EXE_EXT)
	@echo "Stripping symbols..."
	$(STRIP) $(TARGET)$(EXE_EXT)
	@echo.
	@echo "=== Release Build Complete ==="
	@echo.

# ========== 运行和测试 ==========

# 运行程序
run: $(TARGET)$(EXE_EXT)
	@echo.
	@echo "=== Running $(TARGET)$(EXE_EXT) ==="
	@echo.
	@.\$(TARGET)$(EXE_EXT)

# 运行调试版本
run-debug: $(TARGET_DEBUG)$(EXE_EXT)
	@echo.
	@echo "=== Running $(TARGET_DEBUG)$(EXE_EXT) ==="
	@echo.
	@.\$(TARGET_DEBUG)$(EXE_EXT)

# 测试
test: $(TARGET)$(EXE_EXT)
	@echo.
	@echo "=== Running Tests ==="
	@echo.
	@.\$(TARGET)$(EXE_EXT)
	@echo.
	@echo "=== Tests Complete ==="
	@echo.

# ========== 代码分析 ==========

# 静态分析
analyze:
	@echo "Running static analysis..."
	$(CC) $(CFLAGS) $(INCLUDES) -fanalyzer $(SOURCES) -c

# 代码格式检查
check:
	@echo "Checking code style..."
	@echo "TODO: Add code style checker (e.g., clang-format)"

# ========== 清理目标 ==========

# 清理构建文件
clean:
	@echo "Cleaning build files..."
	-@$(RM) *.o *.d 2>$(NULL_DEV) || echo > $(NULL_DEV)
	-@$(RM) *_debug.o 2>$(NULL_DEV) || echo > $(NULL_DEV)
	-@$(RM) $(TARGET)$(EXE_EXT) 2>$(NULL_DEV) || echo > $(NULL_DEV)
	-@$(RM) $(TARGET_DEBUG)$(EXE_EXT) 2>$(NULL_DEV) || echo > $(NULL_DEV)
	-@$(RM) $(LIBRARY_STATIC) 2>$(NULL_DEV) || echo > $(NULL_DEV)
	@echo "Clean completed"

# 深度清理（包括备份文件等）
distclean: clean
	@echo "Deep cleaning..."
	-@$(RM) *~ *.bak *.swp 2>$(NULL_DEV) || echo > $(NULL_DEV)
	@echo "Distclean completed"

# ========== 信息显示 ==========

# 显示变量信息
info:
	@echo "=== Build Configuration ==="
	@echo "CC:          $(CC)"
	@echo "CFLAGS:      $(CFLAGS)"
	@echo "OPT_FLAGS:   $(OPT_FLAGS)"
	@echo "DEBUG_FLAGS: $(DEBUG_FLAGS)"
	@echo "INCLUDES:    $(INCLUDES)"
	@echo "LDFLAGS:     $(LDFLAGS)"
	@echo "LDLIBS:      $(LDLIBS)"
	@echo.
	@echo "=== Files ==="
	@echo "TARGET:      $(TARGET)$(EXE_EXT)"
	@echo "SOURCES:     $(SOURCES)"
	@echo "OBJECTS:     $(OBJECTS)"
	@echo "DEPS:        $(DEPS)"
	@echo.

# 帮助信息
help:
	@echo "=== Queue v1 Makefile - Available Targets ==="
	@echo.
	@echo "Build Targets:"
	@echo "  all          - Build release version (default)"
	@echo "  debug        - Build debug version with sanitizers"
	@echo "  release      - Build optimized release version with LTO"
	@echo "  lib          - Build static library"
	@echo.
	@echo "Run Targets:"
	@echo "  run          - Build and run release version"
	@echo "  run-debug    - Build and run debug version"
	@echo "  test         - Build and run tests"
	@echo.
	@echo "Analysis Targets:"
	@echo "  analyze      - Run static analysis"
	@echo "  check        - Check code style"
	@echo.
	@echo "Clean Targets:"
	@echo "  clean        - Remove build artifacts"
	@echo "  distclean    - Remove all generated files"
	@echo.
	@echo "Info Targets:"
	@echo "  info         - Show build configuration"
	@echo "  help         - Show this help message"
	@echo.
	@echo "Examples:"
	@echo "  mingw32-make              # Build release version"
	@echo "  mingw32-make debug        # Build debug version"
	@echo "  mingw32-make run          # Build and run"
	@echo "  mingw32-make test         # Run tests"
	@echo "  mingw32-make clean        # Clean build files"
	@echo.

# ========== 伪目标声明 ==========
.PHONY: all debug lib release run run-debug test analyze check clean distclean info help

# ========== 包含依赖文件 ==========
-include $(DEPS)
