#ifndef LLAMA_LOGGER_HH
#define LLAMA_LOGGER_HH

#include <llama/type.hh>

enum Type
{
	trace,
	debug,
	info,
	warn,
	error,
	fatal
};

int32 llama_console(Type type, const char * formatstring, ...);
int32 llama_console(const char * title, Type type, const char * formatstring, ...);
int32 llama_console(const char * title, const char * formatstring, ...);
int32 llama_console(const char * formatstring, ...);

void llama_console_show_color(bool state);


#endif
