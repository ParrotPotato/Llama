#include "sprite.hh"

#include "texture_manager.hh"

#include <llama/type.hh>
#include <llama/logger.hh>

// this should be load sprite with texture
void * llama_sprite_load(char * filename, glm::vec2 position, glm::vec2 dim)
{
    Sprite * sprite = (Sprite *) malloc(sizeof(Sprite));

    if(sprite == nullptr) 
    {
        llama_console("Sprite Load", "Unabel to create sprite handler instance\n");
        return nullptr;
    }

    sprite->texture_id = llama_load_texture_2d(filename);
    sprite->dim = dim;
    sprite->position = position;

    return (void *)sprite;
}

void llama_sprite_unload(void * spriteptr)
{
    if(spriteptr == nullptr) return ;

    Sprite * sprite = (Sprite* ) spriteptr;
    llama_unload_texture_2d(sprite->texture_id);

    free(sprite);
}