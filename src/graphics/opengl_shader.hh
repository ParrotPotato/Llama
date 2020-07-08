#ifndef LLAMA_OPENGL_SHADER_HH
#define LLAMA_OPENGL_SHADER_HH

#include <GL/glew.h>

struct Opengl_Shader
{
	GLuint vertex_shader;
	GLuint fragment_shader;

	GLuint program;
};

void * llama_load_shader_program(char * vertex_shader_source, char * fragment_shader_source);

void llama_unload_shader_program(void * shaderptr);

#endif
