#ifndef LLAMA_WINDOW_HH
#define LLAMA_WINDOW_HH

#include <llama/type.hh>

#include <SDL2/SDL.h>

struct Window 
{
	SDL_Window * sdlwindow;
	SDL_GLContext sdlcontext;

	int32 width;
	int32 height;
};

Window * llama_get_window_handler(const char * buffer = nullptr, int32 width = 0, int32 height = 0);

void llama_update_window(Window * winptr);
void llama_clear_window(Window * winptr);

void llama_set_clear_color(void * winptr, real32 r, real32 g, real32 b, real32 a);
void llama_set_depth(Window * winptr, real32 depth);

#endif 
