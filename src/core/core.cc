#include "core.hh"

#include <SDL2/SDL.h>

void llama_engine_init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

void llama_engine_quit()
{
	SDL_Quit();
}
