#include "window.hh"

#include <GL/glew.h>

#include <cassert>

Window * llama_create_window(const char * buffer, int32 width, int32 height)
{
	Window * winptr = (Window *) malloc(sizeof(Window));
	assert(winptr);

	bzero(winptr, sizeof(Window));

	winptr->sdlwindow = SDL_CreateWindow(buffer, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	assert(winptr->sdlwindow);

	winptr->sdlcontext = SDL_GL_CreateContext(winptr->sdlwindow);
	assert(winptr->sdlcontext);

	GLenum init_status = glewInit();
	assert(init_status == GLEW_OK);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	
	winptr->width = width;
	winptr->height= height;

	return winptr;
}

void llama_update_window(void * winptr)
{
	SDL_GL_SwapWindow(((Window *)(winptr))->sdlwindow);
}

void llama_clear_window(void * winptr)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void llama_set_clear_color(void * winptr, real32 r, real32 g, real32 b, real32 a)
{
	glClearColor(r, g, b, a);
}

void llama_set_depth(void * winptr, real32 depth)
{
	glClearDepth(depth);
}
