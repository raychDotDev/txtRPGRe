CC=clang++

BIN_DIR=bin
LIB_DIR=lib
INC_DIR=include
SRC_DIR=src
OBJ_DIR=obj
ASSET_DIR=assets
# add to compile_commands if lsp goes crazy
# -target x86_64-mingw64 
CFLAGS=-std=c++17 -Wall -static-libgcc -static-libstdc++ -pthread -g -O0
LDFLAGS=-I$(INC_DIR) -I$(INC_DIR)/data -L$(LIB_DIR) -lSDL2 -lSDL2_image -lopengl32 -lgdi32 -lwinmm

TARGET=game.exe

SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJ=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)
	cp $(LIB_DIR)/*.dll $(BIN_DIR)/
	cp -r $(ASSET_DIR)/ $(BIN_DIR)/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

rebuild: clean all

run:
	$(BIN_DIR)/$(TARGET)

build-run: all run

rebuild-run: rebuild run
