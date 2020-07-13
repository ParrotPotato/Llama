#include "imm_renderer.hh"

#include "mesh.hh"

#include <llama/type.hh>

#include <GL/glew.h>

// @Fixme : do not use iostream for writing logs to buffer
#include <iostream>

void llama_imm_renderer_entity(void * entity)
{
	// renders a generic entity which have mesh as an 
	// data member 
	
//	std::cout << "renderer_entity : not implemented yet - returning without error \n";

	return;
}

void llama_imm_renderer_mesh(void * meshptr)
{
//	std::cout << "renderer_mesh : currently rendering only positions \n";
// 	std::cout << "renderer_mesh : colors / textures and uvs are diabled\n";

	Mesh * mesh = (Mesh *) meshptr;

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

	for(uint64 i = 0 ; i < mesh->index_count ; i++)
	{
		glVertex3f(mesh->vertices[mesh->indices[i]].pos.x,
				   mesh->vertices[mesh->indices[i]].pos.y,
				   mesh->vertices[mesh->indices[i]].pos.z);
	}

	glEnd();

}

