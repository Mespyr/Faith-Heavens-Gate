# SDL2
SDL_LIB=-L/usr/lib -lSDL2 -lSDL2_image
SDL_INCLUDE=-I/usr/local/include

CPP=g++
CPPFLAGS=-Wall -Wextra -pedantic $(SDL_INCLUDE) -D_REENTRANT
LDFLAGS=$(SDL_LIB)
# directories
SRC_DIR=src
ENGINE_SRC_DIR=src/engine
OBJ_DIR=obj
INCLUDE_DIR=src/include
# src files
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
ENGINE_SRC_FILES=$(wildcard $(ENGINE_SRC_DIR)/*.cpp)
# object files
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
ENGINE_OBJ_FILES=$(patsubst $(ENGINE_SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(ENGINE_SRC_FILES))

HDR_FILES=$(wildcard $(INCLUDE_DIR)/*.h)
BIN=pants

all: $(BIN)

$(BIN): $(OBJ_FILES) $(ENGINE_OBJ_FILES) $(OBJ_DIR)
	$(CPP) $(OBJ_FILES) $(ENGINE_OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(ENGINE_SRC_DIR)/%.cpp $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) $(BIN)
