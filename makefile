cc := g++
libs := -lSDL2 -lGLEW -lGLU -lGL

cpp_flags := --std=c++11

obj_dir := ./bin

bin_dir := $(shell cd ./bin && pwd)
header_dir := $(shell cd ./header && pwd)

central_headers := ./src/utils/resource_loader.hh ./src/utils/parser.hh ./src/utils/logger.hh

output := ./bin/llama.out

driver := 1

debug: build_type = debug
debug: cpp_flags += -g
debug: build

release: build_type = release
release: cpp_flags += -O3
release: build



build: createheader core graphics utils main 
	$(cc) $(cpp_flags) -o $(output) $(bin_dir)/*.o $(libs)

main:
	make $(build_type) --directory="./src" bin_dir=$(bin_dir) header_dir=$(header_dir)

core: 
	make $(build_type) --directory="./src/core" bin_dir=$(bin_dir) header_dir=$(header_dir)

graphics:
	make $(build_type) --directory="./src/graphics" bin_dir=$(bin_dir) header_dir=$(header_dir)

createheader:
	for header in $(central_headers) ; do \
		cp $$header ./header/llama/ ; \
	done
	

utils:
	make $(build_type) --directory="./src/utils" bin_dir=$(bin_dir) header_dir=$(header_dir)



clean:
	rm $(obj_dir)/*.o $(obj_dir)/*.out 2> /dev/null

run:
	cd ./res && DRI_PRIME=$(driver) $(bin_dir)/llama.out

gdb:
	cd ./res && DRI_PRIME=$(driver) gdb $(bin_dir)/llama.out
