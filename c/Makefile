# Makefile to compile programs
# src/ - source files *.cpp
# obj/ - object file  *.o
# bin/ - exec files   *
# Author: Aldo Nunez

CC := gcc
FLAGS := -Wall
LIBS := -lmraa

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=obj/%.o)
BIN := $(OBJ:obj/%.o=bin/%)	

all: $(BIN) $(OBJ)

bin/%: obj/%.o
	$(CC) -o $@  $< $(LIBS) $(FLAGS)

obj/%.o: src/%.c
	@echo "Compiling:"  $<
	$(CC) -o $@  -c $<

.PHONY: clean

clean:
	@echo "Cleaning"
	rm -f $(OBJ) $(BIN) 
