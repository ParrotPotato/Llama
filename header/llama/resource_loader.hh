#ifndef LLAMA_UTILS_RESOURCE_LOADER_HH
#define LLAMA_UTILS_RESOURCE_LOADER_HH


enum struct Resource_Flag 
{
    DISPOSABLE,
    LIVE
};

char * llama_load_file_buffer(char * filename, Resource_Flag flag = Resource_Flag::DISPOSABLE );
void llama_unload_file_buffer(char * filebuffer);

#endif
