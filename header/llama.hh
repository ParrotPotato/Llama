#ifndef LLAMA_ENGINE_HH
#define LLAMA_ENGINE_HH

#include "type.hh"

// Core Handlers
extern void llama_engine_init(void);
extern void llama_engine_quit(void);

// Window Handlers
typedef void * WindowHandler;
extern WindowHandler llama_create_window(const char * buffer, int32 width, int32 height);

extern void llama_update_window(WindowHandler winptr);
extern void llama_clear_window(WindowHandler winptr);
extern void llama_set_clear_color(WindowHandler winptr, real32 r, real32 g, real32 b, real32 a);
extern void llama_set_depth(WindowHandler winptr, real32 depth);

// Typedefs for periferals 
typedef void * KeyboardHandler;

// Event Handlers 
extern KeyboardHandler llama_get_keyboard(void);
extern void llama_event_update(void);
extern bool llama_exit_requested(void);

// Keyboard  Event handlers 
extern bool llama_key_down(KeyboardHandler keyboardhandler, int32 keycode);
extern bool llama_key_up(KeyboardHandler keyboardhandler, int32 keycode);
extern bool llama_key_pressed(KeyboardHandler keyboardhandler, int32 keycode);
extern bool llama_key_released(KeyboardHandler keyboardhandler, int32 keycode);



#endif 
