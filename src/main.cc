#include <llama.hh>

#include <SDL2/SDL.h>

#include <iostream>

#include <unordered_map>

int main()
{
	llama_engine_init();

	WindowHandler window = llama_create_window("Llama", 800, 600);

	llama_set_clear_color(window, 0.18f, 0.32f, 0.93f, 1.0f);
	llama_set_depth(window, 1.0f);

	llama_clear_window(window);
	llama_update_window(window);

	KeyboardHandler keyboardHandler = llama_get_keyboard();

	while(llama_exit_requested()  == false && llama_key_pressed(keyboardHandler, SDL_SCANCODE_ESCAPE)  == false )
	{
		if(llama_key_pressed(keyboardHandler, SDL_SCANCODE_A)){std::cout << "A key pressed\n";}
		else if(llama_key_pressed(keyboardHandler, SDL_SCANCODE_B)){std::cout << "B key pressed\n";}

		llama_event_update();
	}

	llama_engine_quit();
	return 0;
}
