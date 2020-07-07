#ifndef LLAMA_KEYBOARD_HH
#define LLAMA_KEYBOARD_HH

#include <type.hh>

struct KeyboardState
{
	int32 KEY_COUNT;
	bool curstate[1000];
	bool prvstate[1000];
};

bool llama_key_down(void * keyboardptr, int32 keycode);
bool llama_key_up(void * keyboardptr, int32 keycode);

bool llama_key_pressed(void * keyboardptr, int32 keycode);
bool llama_key_released(void * keyboardptr, int32 keycode);

void llama_init_keyboard(void * keyboardptr);


#endif 
