CC = gcc
SRC = src/main.c src/editor.c
BIN = bin/melon

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p bin
	$(CC) -Iinclude $(SRC) -o $(BIN) -lncurses

clean:
	rm -f $(BIN)
