# Makefile to compile programs
# src/ - source files *.cpp
# obj/ - object file  *.o
# bin/ - exec files   *
# Author: Aldo Nunez

CC := g++
FLAGS := -Wall
LIBS := -lmraa


SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=obj/%.o)
BIN := $(OBJ:obj/%.o=bin/%)	

all: $(BIN) $(OBJ)

bin/%: obj/%.o
	$(CC) -o $@  $< $(LIBS) $(FLAGS)

obj/%.o: src/%.cpp
	@echo "Compiling:"  $<
	$(CC) -o $@  -c $<

.PHONY: clean
#
clean:
	@echo "Cleaning"
	rm -f $(OBJ) $(BIN)
