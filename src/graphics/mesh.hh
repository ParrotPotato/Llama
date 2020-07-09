#ifndef LLAMA_MESH_HH
#define LLAMA_MESH_HH

#include <llama/type.hh>

#include <glm/glm.hpp>

#include <vector>

struct Vertex;

struct Mesh 
{
	Vertex * vertices;
	uint64 vertex_count;

	uint32 * indices;
	uint64 index_count;
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 colors;
	glm::vec3 normal;
	glm::vec2 uv;
};

void * llama_load_mesh(char * filename);
void llama_unload_mesh(void * meshptr);

#endif 
