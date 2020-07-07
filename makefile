cc := g++
libs := -lSDL2 -lGLEW -lGLU -lGL

cpp_flags := --std=c++11

obj_dir := ./bin

bin_dir := $(shell cd ./bin && pwd)
header_dir := $(shell cd ./header && pwd)

output := ./bin/llama.out

debug: build_type = debug
debug: cpp_flags += -g
debug: build

release: build_type = release
release: cpp_flags += -O3
release: build

build: core main
	@$(cc) $(cpp_flags) -o $(output) $(bin_dir)/*.o $(libs)

main:
	@make $(build_type) --directory="./src" bin_dir=$(bin_dir) header_dir=$(header_dir)

core: 
	@make $(build_type) --directory="./src/core" bin_dir=$(bin_dir) header_dir=$(header_dir)

clean:
	@rm $(obj_dir)/*.o $(obj_dir)/*.out 2> /dev/null

run:
	./bin/llama.out
