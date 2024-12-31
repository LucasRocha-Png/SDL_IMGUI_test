PROJECT = amadeus
BUILD_FOLDER = build
COPY_FOLDER = ${PROJECT}

SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)

IMGUI_SRC = $(wildcard imgui/*.cpp)
IMGUI_HEADERS = $(wildcard imgui/*.h)

OBJECT_FOLDER = bin
OBJECTS = $(patsubst src/%.cpp, $(OBJECT_FOLDER)/%.o, $(SRC)) \
          $(patsubst imgui/%.cpp, $(OBJECT_FOLDER)/%.o, $(IMGUI_SRC))

CC = x86_64-w64-mingw32-g++
INCLUDE_FOLDER = -Iinclude/SDL2 -Iinclude -Iinclude/imgui -Iimgui
LINK_FLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -static-libgcc -static-libstdc++
COMPILE_FLAGS = -Wall -Wextra -pedantic -std=c++11 -mconsole

all: MKFOLDER $(BUILD_FOLDER)/$(PROJECT).exe

$(BUILD_FOLDER)/$(PROJECT).exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_FOLDER)/$(PROJECT).exe $(LINK_FLAGS)

$(OBJECT_FOLDER)/%.o: src/%.cpp include/%.h
	$(CC) $< $(INCLUDE_FOLDER) $(COMPILE_FLAGS) -c -o $@

$(OBJECT_FOLDER)/%.o: imgui/%.cpp
	$(CC) $< $(INCLUDE_FOLDER) $(COMPILE_FLAGS) -c -o $@

MKFOLDER:
	@ mkdir -p $(BUILD_FOLDER) $(OBJECT_FOLDER)

clean:
	rm -rf $(BUILD_FOLDER)/$(PROJECT).exe
	rm -rf $(OBJECT_FOLDER)/*.o
	rm -rf ${COPY_FOLDER}
	rm -f ${PROJECT}.zip

run: $(BUILD_FOLDER)/$(PROJECT).exe
	$(BUILD_FOLDER)/$(PROJECT).exe

copy: $(BUILD_FOLDER)/$(PROJECT).exe
	mkdir -p ${COPY_FOLDER}
	cp $(BUILD_FOLDER)/$(PROJECT).exe ${COPY_FOLDER}
	cp bin/*.dll ${COPY_FOLDER}
	cp -r assets ${COPY_FOLDER}
	zip -r ${PROJECT}.zip ${COPY_FOLDER}

.PHONY: clean MKFOLDER run copy
