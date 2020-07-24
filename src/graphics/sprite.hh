#ifndef LLAMA_SPRITE_HH 
#define LLAMA_SPRITE_HH

#include "mesh.hh"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

struct Sprite
{
	Mesh * mesh = nullptr;
    GLuint texture_id = 0;
};

void * llama_sprite_load(char * filename, glm::vec2 position = glm::vec2(0.0f, 0.0f), glm::vec2 dim = glm::vec2(16.0f, 16.0f));
void llama_sprite_unload(void * spriteptr);


#endif
