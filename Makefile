# $< first requirement
# $@ target
# $^ all requirements

PROJECT = amadeus
BUILD_FOLDER = build

SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)

OBJECT_FOLDER = bin
OBJECTS = $(patsubst src/%.cpp, $(OBJECT_FOLDER)/%.o, $(SRC))

CC = x86_64-w64-mingw32-g++
INCLUDE_FOLDER = -Iinclude/SDL2
LINK_FLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 
COMPILE_FLAGS = -Wall -Wextra -pedantic -std=c++11


all: MKFOLDER $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_FOLDER)/$(PROJECT).exe $(LINK_FLAGS)

$(OBJECT_FOLDER)/%.o: ./src/%.cpp ./include/%.h
	$(CC) $< $(INCLUDE_FOLDER) $(COMPILE_FLAGS) -c -o $@

MKFOLDER:
	@ mkdir -p $(BUILD_FOLDER)

clean:
	rm -rf $(BUILD_FOLDER)/$(PROJECT).exe
	rm -rf $(OBJECT_FOLDER)/*.o

.PHONY: clean MKFOLDER
