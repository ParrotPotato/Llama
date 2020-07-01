CC := g++ 
INCLUDE := -D_REENTRANT -I/usr/include/SDL2 
LIBS := -lSDL2 -lGLEW -lGLU -lGL

CPPFLAGS := --std=c++11

SRC_DIR := ./src
OBJ_DIR := ./bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cc)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC_FILES))

debug: CPPFLAGS += -g
debug: $(OBJ_DIR)/llama.out

release: CPPFLAGS += -O3
release: $(OBJ_DIR)/llama.out

$(OBJ_DIR)/llama.out: $(OBJ_FILES)
	g++ -o $@ $^ $(CPPFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	g++ -c -o $@ $^ $(CPPFLAGS) $(LIBS)

clean:
	rm $(OBJ_DIR)/*.o $(OBJ_DIR)/*.out 2> /dev/null

run: 
	./bin/llama.out
