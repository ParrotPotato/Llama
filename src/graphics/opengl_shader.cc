#include "opengl_shader.hh"

#include <llama/type.hh>

#include <GL/glew.h>

#include <cstdlib>
#include <cstdio>


// @Temperory: Use logger for displaying the shader logs and other 
// buffer messages
#include <iostream>

char * load_shader_source_buffer(char * shader_source)
{
	char * source = nullptr;

	FILE * fp = fopen(shader_source, "r");
	if(fp == nullptr) 
	{
		// @Fixme: Use logger instead of iostream for logging 
		// internal engine errors

		std::cout << "Unable to open shader file " << shader_source << "\n";
		perror("");
		return source;
	}

	fseek(fp, 0L, SEEK_END);
	int64 size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	source = (char *) malloc(size + 2);
	uint64 readsize = fread(source, sizeof(char), size, fp);

	fclose(fp);

	source[readsize] = '\0';

	return source;
}

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

		// @Fixme: Use logger instead of iostream for logging 
		// internal engine errors

		std::cout << "Error occured while compiling shader \n";
		std::cout << log_buffer << "\n";

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}


void * llama_load_shader_program(char * vertex_shader_source, char * fragment_shader_source)
{
	char * vertex_shader_source_buffer   = load_shader_source_buffer(vertex_shader_source);
	char * fragment_shader_source_buffer = load_shader_source_buffer(fragment_shader_source);

	if(vertex_shader_source_buffer == nullptr || fragment_shader_source_buffer == nullptr) 
	{
		std::cout << "Unable to source buffer \n";
		return nullptr;
	}

	GLuint vertex_shader   = compile_shader(vertex_shader_source_buffer, GL_VERTEX_SHADER);
	GLuint fragment_shader = compile_shader(fragment_shader_source_buffer, GL_FRAGMENT_SHADER);

	if(vertex_shader == 0 || fragment_shader_source == 0)
	{
		// @Fixme: Use logger instead of iostream for logging 
		// internal engine errors

		std::cout << "Error occured while parsing one of the shaders\n";

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

			// @Fixme: Use logger instead of iostream for logging 
			// internal engine errors

			std::cout << "Error occure while linking shaders \n";
			std::cout << log_buffer << "\n";

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

			// @Fixme: Use logger instead of iostream for logging 
			// internal engine errors

			std::cout << "Error found while validating shaders \n";
			std::cout << log_buffer << "\n";

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
