CC = gcc
CFLAGS = -Wall -std=c99
SRC_DIR = .
CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lgmp 

all: main

main: obj/main.o obj/big_int.o
	$(CC) $(CFLAGS) -o bin/main.exe obj/big_int.o obj/main.o $(LIBS)

obj/main.o: main.c
	$(CC) $(CFLAGS) -c -o obj/main.o main.c

obj/big_int.o: big_int.c
	$(CC) $(CFLAGS) -c -o obj/big_int.o big_int.c

	
OBJ_DIR = obj
BIN_DIR = bin
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/main.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /q $(OBJ_DIR)\*.o
	del /q $(EXECUTABLE)
	rm -f obj/*.o bin/main.exe

