#include "texture_manager.hh"

#include <llama/type.hh>
#include <llama/resource_loader.hh>
#include <llama/logger.hh>

#define STB_IMAGE_IMPLEMENTATION
#include <llama/stb_image.hh>

#include <GL/glew.h>

#include <unordered_map>
#include <string>

std::unordered_map<std::string, GLuint> texture_lookup_table;

GLuint llama_load_texture_2d(char * filename, Texture_Load_Flag flag)
{
    std::string texture_source(filename);

    if(texture_lookup_table.find(texture_source) == texture_lookup_table.end())
    {
        llama_console("Load Texture", "Loading new texture : %s\n", texture_source.c_str());

        int32 width, height, nrchannel;

        unsigned char * buffer = stbi_load(texture_source.c_str(), &width, &height, &nrchannel, 0);

        if(buffer == nullptr)
        {
			llama_console("Load Texture", "Read data :\n width : %d\n height : %d\n nrchannel : %d\n", width, height, nrchannel);
            llama_console("Load Texture", error, "Unable to load texture file (%s)\n", filename);
            return 0;
        }

		GLuint texture_id = 0;

		glGenTextures(1, &texture_id);

		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(buffer);

		texture_lookup_table[texture_source] = texture_id;
	}

    return texture_lookup_table[texture_source];
}

void llama_unload_texture_2d(char * filename)
{
    if(texture_lookup_table.find(std::string(filename)) == texture_lookup_table.end()) return;
    glDeleteTextures(GL_TEXTURE_2D, &texture_lookup_table[filename]);
}

void llama_unload_texture_2d(GLuint texture_id)
{
    glDeleteTextures(GL_TEXTURE_2D, &texture_id);
}
