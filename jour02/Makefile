CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = jour02
SRC = jour02.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	@echo "Execution"
	./$(TARGET)

test: $(TARGET)
	@echo "=== Test avec l'exemple (02.example) ==="
	./$(TARGET) 02.example

clean:
	rm -f $(TARGET)

.PHONY: all run test clean
