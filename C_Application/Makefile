
CC = gcc

CFLAGS = -Wall -Wextra -I./src

SRC = $(wildcard src/*.c) \
      $(wildcard src/models/*c)

TARGET = app

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
