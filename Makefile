CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =
SRC_DIR = .
UTILS_DIR = ./utils
TARGET = vm

SRC = $(SRC_DIR)/main.c
UTILS = $(UTILS_DIR)/stack.c

OBJS = $(SRC:.c=.o) $(UTILS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
