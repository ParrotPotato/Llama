#include "opengl_shader.hh"

#include <llama/type.hh>
#include <llama/resource_loader.hh>
#include <llama/logger.hh>

#include <GL/glew.h>

#include <cstdlib>
#include <cstdio>


GLuint compile_shader(char * shader_source, GLenum type)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &shader_source, nullptr);
	glCompileShader(shader);

	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(success == GL_FALSE)
	{
		GLint log_size = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		char * log_buffer = (char *) alloca(log_size * sizeof(char));
		glGetShaderInfoLog(shader, log_size, nullptr, log_buffer); 

		llama_console("compile shader", warn, "Error occured while compiling shader\n %s\n", log_buffer);

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}


void * llama_load_shader_program(char * vertex_shader_source, char * fragment_shader_source)
{
	char * vertex_shader_source_buffer   = llama_load_file_buffer(vertex_shader_source);
	char * fragment_shader_source_buffer = llama_load_file_buffer(fragment_shader_source);

	if(vertex_shader_source_buffer == nullptr || fragment_shader_source_buffer == nullptr) 
	{
		llama_console("load shader program", "Unable to source buffer\n");
		return nullptr;
	}

	GLuint vertex_shader   = compile_shader(vertex_shader_source_buffer, GL_VERTEX_SHADER);
	GLuint fragment_shader = compile_shader(fragment_shader_source_buffer, GL_FRAGMENT_SHADER);

	if(vertex_shader == 0 || fragment_shader_source == 0)
	{
		llama_console("load shader program", "Error occured while parsing one of the shaders\n");
		return nullptr;
	}

	GLuint program = glCreateProgram();
	
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);

	{
		GLint linked_success = GL_TRUE;
		glGetProgramiv(program, GL_LINK_STATUS, &linked_success);

		if(linked_success == GL_FALSE)
		{
			GLint log_size = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);

			char * log_buffer = (char *) alloca(log_size * sizeof(char));
			glGetProgramInfoLog(program, log_size, nullptr, log_buffer);

			llama_console("linking shader", "Error occured while linking shaders\n%s\n", log_buffer);

			return nullptr;
		}
	}

	glValidateProgram(program);

	{
		GLint validate_success = GL_TRUE;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_success);

		if(validate_success == GL_FALSE)
		{
			GLint log_size = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);

			char * log_buffer = (char *) alloca(log_size * sizeof(char));
			glGetProgramInfoLog(program, log_size, nullptr, log_buffer);

			llama_console("validate program", "Error found while validating program\n%s\n", log_buffer);

			return nullptr;
		}
	}

	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);

	// @Note @Improvement: Not deleting vertex and fragment shaders after compilation for 
	// debugging purposes

	Opengl_Shader * shader = (Opengl_Shader *) malloc(sizeof(Opengl_Shader));
	shader->vertex_shader   = vertex_shader;
	shader->fragment_shader = fragment_shader;

	shader->program = program;

	return shader;
}

void llama_unload_shader_program(void * shaderptr)
{
	Opengl_Shader * shader = (Opengl_Shader *) shaderptr;

	if(shader == nullptr) return;

	glDetachShader(shader->program, shader->vertex_shader);
	glDetachShader(shader->program, shader->fragment_shader);

	glDeleteShader(shader->vertex_shader);
	glDeleteShader(shader->fragment_shader);

	glDeleteProgram(shader->program);
}

void llama_use_shader_program(void * shaderptr)
{
	Opengl_Shader * shader = (Opengl_Shader *) shaderptr;

	// checking if valid shader 
	if(shader == nullptr || shader->program == 0) return;

	glUseProgram(shader->program);
}

void llama_unuse_shader_program(void)
{
	glUseProgram(0);
}
