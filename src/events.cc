#include "events.hh"

#include "type.hh"
#include "keyboard.hh"

#include <SDL2/SDL.h> 

#include <vector>
#include <iostream> 

#include <cassert>

KeyboardState * keyboard = nullptr;
bool exit_requested = false;

void * llama_get_keyboard(void)
{
	if(!keyboard)
	{
		keyboard = (KeyboardState *) malloc(sizeof(KeyboardState));
		assert(keyboard);
		llama_init_keyboard(keyboard); 
	}

	return keyboard;
}

void llama_event_update(void)
{
	if(keyboard)
	{
		for(int32 i=0 ; i < keyboard->KEY_COUNT ; i++)
		{
			keyboard->prvstate[i] = keyboard->curstate[i];
		}
	}

	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				exit_requested = true;
				break;

			case SDL_KEYDOWN:
				if(keyboard)
				{
					if(keyboard->KEY_COUNT > event.key.keysym.scancode)
						keyboard->curstate[event.key.keysym.scancode] = true;
				}
				break;
			case SDL_KEYUP: 
				if(keyboard)
				{
					if(keyboard->KEY_COUNT > event.key.keysym.scancode)
						keyboard->curstate[event.key.keysym.scancode] = false;
				}
				break;
		}
	}
	return;
}

bool llama_exit_requested(void)
{
	return exit_requested;
}
