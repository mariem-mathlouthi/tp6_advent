CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = jour01
SRC = jour01.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) 01.input

clean:
	rm -f $(TARGET) *.o

.PHONY: all run clean
