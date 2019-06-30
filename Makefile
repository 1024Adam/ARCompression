# Binary File
OBJ := arc

# Source Files
SRC_DIR := src/huffman/
SOURCE_FILES := $(wildcard $(SRC_DIR)*.c)

# Object Files
OBJ_DIR := bin/huffman/
OBJECT_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SOURCE_FILES))

# Header Files
HEADER_DIR := include/
INCLUDE := -I$(HEADER_DIR)

# Depend Files
DEPEND_DIR := depend/
DEPEND_FILES := $(patsubst $(SRC_DIR)%.c,$(DEPEND_DIR)%.d,$(SOURCE_FILES))

# Compiler
CC := gcc

# C Compiler Flags
STD := -std=c11
# development (3), and production (0)
DEBUG := -g3
# Optimizations
OPT := -O2 -flto

# Dependency Flags
DFLAGS := -MMD -MF

CFLAGS += -Werror -Wall -Wextra -Wpedantic $(DEBUG)
LFLAGS := -lm

.PHONY: all

all: $(OBJ)

$(OBJ): $(OBJECT_FILES)
	$(CC) $(DEBUG) $(STD) $(OBJECT_FILES) $(LFLAGS) -o $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< $(CFLAGS) $(STD) $(INCLUDE) $(OPT) $(DFLAGS) $(patsubst $(OBJ_DIR)%.o,$(DEPEND_DIR)%.d,$@) -o $@

-include $(DEPEND_FILES)

.PHONY: valgrind clean

clean:
	rm -f $(OBJ_DIR)*.o
	rm -f $(DEPEND_DIR)*.d
	rm -f $(OBJ)

valgrind: all
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes ./$(OBJ)

alias:
	if [ "$(UNAME_S)" = "Linux" ]; \
        then \
	    printf "%s%s%s" "alias arcompress='" $(PWD) "/arc'" >> ~/.bashrc;\
	else\
	    printf "%s%s%s" "alias arcompress='" $(PWD) "/arc'" >> ~/.bash_profile;\
	fi
