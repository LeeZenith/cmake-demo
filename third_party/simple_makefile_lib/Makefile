# 简单Makefile示例
CC = gcc
CFLAGS = -Wall -O2
TARGET = libsimple.a
SRCS = simple.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

install:
	mkdir -p lib include
	cp $(TARGET) lib/
	cp simple.h include/