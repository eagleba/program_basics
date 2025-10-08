# 传感器数据传输演示程序 Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lzmq -lpthread
TARGETS = producer consumer
SOURCES = common.c

# 默认目标
all: $(TARGETS)

# 编译生产者
producer: producer.c $(SOURCES)
	$(CC) $(CFLAGS) -o producer producer.c $(SOURCES) $(LDFLAGS)

# 编译消费者
consumer: consumer.c $(SOURCES)
	$(CC) $(CFLAGS) -o consumer consumer.c $(SOURCES) $(LDFLAGS)

# 清理
clean:
	rm -f $(TARGETS)

# 运行演示（需要两个终端）
run-demo:
	@echo "请打开两个终端："
	@echo "终端1: make run-consumer"
	@echo "终端2: make run-producer"

# 运行消费者
run-consumer: consumer
	./consumer

# 运行生产者
run-producer: producer
	./producer

# 帮助
help:
	@echo "可用目标："
	@echo "  all         - 编译所有程序"
	@echo "  producer    - 编译生产者"
	@echo "  consumer    - 编译消费者"
	@echo "  clean       - 清理编译文件"
	@echo "  run-demo    - 显示运行说明"
	@echo "  run-consumer- 运行消费者"
	@echo "  run-producer- 运行生产者"
	@echo "  help        - 显示此帮助信息"

.PHONY: all clean run-demo run-consumer run-producer help
