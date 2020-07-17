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

        llama_console("Load Texture", "Loading new texture : %s\n", texture_source);

        char * file_source_buffer = llama_load_file_buffer((char *)texture_source.c_str());

        GLuint texture_id = 0;

        glGenTextures(1, &texture_id);

        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int32 width, height, nrchannel;

        unsigned char * buffer = stbi_load(file_source_buffer, &width, &height, &nrchannel, 0);

        if(buffer)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(buffer);
        }

        else 
        {
            llama_console("Load Texture", "Unable to load texture file (%s)\n", filename);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDeleteTextures(1, &texture_id);
            return 0;
        }

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