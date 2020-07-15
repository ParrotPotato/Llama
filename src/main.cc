#include <llama/llama.hh>

#include <SDL2/SDL.h>

#include <iostream>

#include <unordered_map>


int main()
{
	llama_engine_init();

	WindowHandler window = llama_get_window_handler("Llama", 800, 600);

	llama_set_clear_color(window, 0.0f, 0.0f, 0.0f, 1.0f);
	llama_set_depth(window, 1.0f);

	llama_clear_window(window);
	llama_update_window(window);

	KeyboardHandler keyboard_handler = llama_get_keyboard_handler();

	OpenglShaderHandler shader_handler = llama_load_shader_program(
			"shaders/basic_vertex_shader.glsl",
			"shaders/basic_fragment_shader.glsl");

	MeshHandler mesh_handler = llama_load_mesh("models/cube.obj");

	while(llama_exit_requested()  == false && llama_key_pressed(keyboard_handler, SDL_SCANCODE_ESCAPE)  == false )
	{
		llama_clear_window(window);

		llama_use_shader_program(shader_handler);

		llama_imm_renderer_mesh(mesh_handler);

		llama_unuse_shader_program();

		if(llama_key_pressed(keyboard_handler, SDL_SCANCODE_A)){std::cout << "A key pressed\n";}
		else if(llama_key_pressed(keyboard_handler, SDL_SCANCODE_B)){std::cout << "B key pressed\n";}

		llama_event_update();

		llama_update_window(window);
	}

	llama_unload_mesh(mesh_handler);

	llama_unload_shader_program(shader_handler);

	llama_engine_quit();
	return 0;
}
