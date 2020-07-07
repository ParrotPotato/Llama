bin_dir :="./bin"
header_dir :="./header"

src_dir := ./
obj_dir := $(bin_dir)
src_files := $(wildcard $(src_dir)/*.cc)
obj_files := $(patsubst $(src_dir)/%.cc, $(obj_dir)/%.o, $(src_files))

cc := g++
libs := -lSDL2 -lGLEW -lGLU -lGL
cpp_flags := --std=c++11

debug: cpp_flags += -g
debug: $(obj_files)

release: cpp_flags += -O3
release: $(obj_files)

$(obj_dir)/%.o: $(src_dir)/%.cc
	@$(cc) $(cpp_flags) -c -o $@ $^ $(libs) -I$(header_dir)
