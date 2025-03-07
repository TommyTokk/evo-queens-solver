# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -g

# Source files directory
SRC_DIR = .
LIB_DIR = lib
BIN_DIR = bin

# Source files
MAIN_SRC = $(SRC_DIR)/genetic.c
LIB_SRC = $(LIB_DIR)/lib.c

# Object files
MAIN_OBJ = $(MAIN_SRC:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)

# Executable name
EXECUTABLE = $(BIN_DIR)/genetic

# Default target
all: $(EXECUTABLE)

# Linking the objects
$(EXECUTABLE): $(MAIN_OBJ) $(LIB_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compiling main
$(MAIN_OBJ): $(MAIN_SRC) $(LIB_DIR)/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compiling library
$(LIB_OBJ): $(LIB_SRC) $(LIB_DIR)/lib.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Clean
clean:
	rm -rf $(BIN_DIR)/*.o $(EXECUTABLE) $(LIB_DIR)/*.o $(SRC_DIR)/*.o

# PHONY targets
.PHONY: all clean


