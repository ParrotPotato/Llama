#ifndef LLAMA_TEXTURE_MANAGER_HH
#define LLAMA_TEXTURE_MANAGER_HH

#include <GL/glew.h>

enum struct Texture_Load_Flag
{
    DISPOSABLE,
    LIVE
};

GLuint llama_load_texture_2d(char * filename, Texture_Load_Flag flag = Texture_Load_Flag::LIVE);

void llama_unload_texture_2d(char * filename);
void llama_unload_texture_2d(GLuint texture_id);

#endif