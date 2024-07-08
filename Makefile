# SDL2
SDL_LIB=-L/usr/lib -lSDL2 -lSDL2_image
SDL_INCLUDE=-I/usr/local/include

CPP=g++
CPPFLAGS=-Wall -Wextra -pedantic $(SDL_INCLUDE) -D_REENTRANT
LDFLAGS=$(SDL_LIB)

SRC_DIRS=src src/engine
SRC_FILES=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
HEADERS=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.hpp))

OBJ_DIR=obj
OBJ_FILES=$(foreach dir, $(SRC_DIRS), \
  $(patsubst $(dir)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(dir)/*.cpp)))
BIN=pants

define compile_dir
$(OBJ_DIR)/%.o: $(1)/%.cpp $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) -c $$< -o $$@
endef
$(foreach dir, $(SRC_DIRS), $(eval $(call compile_dir, $(dir))))

all: $(BIN)
$(BIN): $(OBJ_FILES) $(OBJ_DIR)
	$(CPP) $(OBJ_FILES) -o $@ $(LDFLAGS)

format: $(SRC_FILES) $(HEADERS)
	clang-format -i $(SRC_FILES) $(HEADERS) -style=file

$(OBJ_DIR):
	mkdir -p $@
clean:
	$(RM) -r $(OBJ_DIR) $(BIN)
