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

	sprite->mesh.vertices = new Vertex[4];
	sprite->mesh.indices  = new uint32[4];

	sprite->mesh.vertex_count = 4;
	sprite->mesh.index_count = 6;

	{ // initialising vertices and indices for mesh for a sprite

		Vertex * vertice = sprite->mesh.vertices;
		uint32 * indices = sprite->mesh.indices;

		vertice[0].pos = glm::vec3(position.x - dim.x / 2.0f, position.y - dim.y / 2.0f, 0.0f);
		vertice[0].colors = glm::vec3(0.0f, 0.0f, 0.0f);
		vertice[0].normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertice[0].uv  = glm::vec2(0.0f, 0.0f);

		vertice[1].pos = glm::vec3(position.x + dim.x / 2.0f, position.y - dim.y / 2.0f, 0.0f);
		vertice[1].colors = glm::vec3(0.0f, 0.0f, 0.0f);
		vertice[1].normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertice[1].uv  = glm::vec2(1.0f, 0.0f);

		vertice[2].pos = glm::vec3(position.x + dim.x / 2.0f, position.y + dim.y / 2.0f, 0.0f);
		vertice[2].colors = glm::vec3(0.0f, 0.0f, 0.0f);
		vertice[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertice[2].uv  = glm::vec2(1.0f, 1.0f);

		vertice[3].pos = glm::vec3(position.x - dim.x / 2.0f, position.y + dim.y / 2.0f, 0.0f);
		vertice[3].colors = glm::vec3(0.0f, 0.0f, 0.0f);
		vertice[3].normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertice[3].uv  = glm::vec2(0.0f, 1.0f);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

	}

    return (void *)sprite;
}

void llama_sprite_unload(void * spriteptr)
{
    if(spriteptr == nullptr) return ;

    Sprite * sprite = (Sprite* ) spriteptr;
    llama_unload_texture_2d(sprite->texture_id);

    free(sprite);
}
