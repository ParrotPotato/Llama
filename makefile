cc := g++
libs := -lSDL2 -lGLEW -lGLU -lGL

cpp_flags := --std=c++11

src_dir := ./src
obj_dir := ./bin
src_files := $(wildcard $(src_dir)/*.cc)

bin_dir := $(shell cd ./bin && pwd)
header_dir := $(shell cd ./header && pwd)

debug: build_type = debug
debug: cpp_flags += -g
debug: build

release: build_type = release
release: cpp_flags += -O3
release: build

build: core main
build: $(obj_dir)/llama.out

main:
	@make $(build_type) --directory="./src" bin_dir=$(bin_dir) header_dir=$(header_dir)

core: 
	@make $(build_type) --directory="./src/core" bin_dir=$(bin_dir) header_dir=$(header_dir)

$(obj_dir)/llama.out:
	@$(cc) $(cpp_flags) -o $@ $(bin_dir)/*.o $(libs)

clean:
	@rm $(obj_dir)/*.o $(obj_dir)/*.out 2> /dev/null

run:
	./bin/llama.out
