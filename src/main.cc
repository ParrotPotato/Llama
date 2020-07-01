#include "llama.hh"

#include <iostream>

int main()
{
	llama_engine_init();

	WindowHandler window = llama_create_window("Test window", 800, 600);

	llama_set_clear_color(window, 0.18f, 0.32f, 0.93f, 1.0f);
	llama_set_depth(window, 1.0f);

	llama_clear_window(window);
	llama_update_window(window);

	std::cin.get();

	llama_engine_quit();
	return 0;
}
