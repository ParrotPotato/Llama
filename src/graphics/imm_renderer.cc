#include "imm_renderer.hh"

#include "mesh.hh"

#include <llama/type.hh>

#include <GL/glew.h>

void llama_imm_renderer_entity(void * entity)
{
	return;
}

void llama_imm_renderer_mesh(void * meshptr)
{
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

