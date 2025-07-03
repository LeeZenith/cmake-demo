# 模拟被集成的Makefile项目
CC = gcc
CFLAGS = -I./include -fPIC
TARGET = libdemo.a
SRC = src/hello.c src/util.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	mkdir -p $(DESTDIR)/usr/local/lib
	mkdir -p $(DESTDIR)/usr/local/include/demo
	cp libdemo.a $(DESTDIR)/usr/local/lib
	cp include/*.h $(DESTDIR)/usr/local/include/demo

clean:
	rm -f $(OBJ) $(TARGET)