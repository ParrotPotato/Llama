#include "keyboard.hh"

#include <iostream>

bool llama_key_down(void * keyboardptr, int32 keycode)
{
	KeyboardState * keystate = (KeyboardState *) keyboardptr;
	return keystate->curstate[keycode];
}
bool llama_key_up(void * keyboardptr, int32 keycode)
{
	KeyboardState * keystate = (KeyboardState *) keyboardptr;
	return !keystate->curstate[keycode];
}

bool llama_key_pressed(void * keyboardptr, int32 keycode)
{
	KeyboardState * keystate = (KeyboardState *) keyboardptr;
	return (keystate->curstate[keycode] && !keystate->prvstate[keycode]);
}

bool llama_key_released(void * keyboardptr, int32 keycode)
{
	KeyboardState * keystate = (KeyboardState *) keyboardptr;
	return (!keystate->curstate[keycode] && keystate->prvstate[keycode]);
}

void llama_init_keyboard(void * keyboardptr)
{
	KeyboardState * ptr = (KeyboardState *) keyboardptr;
	ptr->KEY_COUNT = 1000;

	for(int32 i = 0 ; i < ptr->KEY_COUNT ; i++)
	{
		ptr->curstate[i] = false;
		ptr->prvstate[i] = false;
	}

	return;
}
