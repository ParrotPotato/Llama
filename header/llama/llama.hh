#ifndef LLAMA_ENGINE_HH
#define LLAMA_ENGINE_HH

#include "type.hh"

#include <GL/glew.h>

// Exposing all the structures just as void pointers
// so as to not expose internal structures to outer
// implementations

// Core Handlers
extern void llama_engine_init(void);
extern void llama_engine_quit(void);

// Window Handlers
typedef void * WindowHandler;

extern WindowHandler llama_get_window_handler(const char * buffer = nullptr, int32 width = 0, int32 height = 0);

extern void llama_update_window(WindowHandler winptr);
extern void llama_clear_window(WindowHandler winptr);
extern void llama_set_clear_color(WindowHandler winptr, real32 r, real32 g, real32 b, real32 a);
extern void llama_set_depth(WindowHandler winptr, real32 depth);

// Typedefs for periferals
typedef void * KeyboardHandler;

// Event Handlers
extern KeyboardHandler llama_get_keyboard_handler(void);
extern void llama_event_update(void);
extern bool llama_exit_requested(void);

// Keyboard  Event handlers
extern bool llama_key_down(KeyboardHandler keyboardhandler, int32 keycode);
extern bool llama_key_up(KeyboardHandler keyboardhandler, int32 keycode);
extern bool llama_key_pressed(KeyboardHandler keyboardhandler, int32 keycode);
extern bool llama_key_released(KeyboardHandler keyboardhandler, int32 keycode);

// Typedefs for opengl_shaders
typedef void * OpenglShaderHandler;

extern OpenglShaderHandler llama_load_shader_program(char * vertex_shader_source, char * fragment_shader_source);
extern void llama_unload_shader_program(OpenglShaderHandler opengl_shader_handler);

extern void llama_use_shader_program(OpenglShaderHandler opengl_shader_handler);
extern void llama_unuse_shader_program(void);

// Mesh data
typedef void * MeshHandler;

extern MeshHandler llama_load_mesh(char * filename);
extern void llama_unload_mesh(MeshHandler meshptr);

// Immediate Renderer 
extern void llama_imm_renderer_entity(void * entity);
extern void llama_imm_renderer_mesh(MeshHandler  mesh);

#endif
