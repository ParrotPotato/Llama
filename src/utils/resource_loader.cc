#include "resource_loader.hh"

#include <llama/type.hh>

#include <cstdio> 

#include <iostream> // @Fixme : not to be used for logging 

char * llama_load_file_buffer(char * filename)
{
	char * buffer = nullptr;

	if(filename == nullptr) return nullptr;

	FILE * fp = fopen(filename, "r");
	if(fp == nullptr) 
	{
		// @Fixme: Use logger instead of iostream for logging 
		// internal engine errors

		std::cout << "Unable to open shader file " << filename << "\n";
		perror("");
		return nullptr;
	}

	fseek(fp, 0L, SEEK_END);
	int64 size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buffer = (char *) malloc(size + 2);
	uint64 readsize = fread(buffer, sizeof(char), size, fp);

	fclose(fp);

	buffer[readsize] = '\0';

	return buffer;
}

void llama_unload_file_buffer(char * filebuffer)
{
	if(filebuffer == nullptr) return;

	free(filebuffer);

	return;
}
