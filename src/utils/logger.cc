#include "logger.hh"

#include <llama/type.hh>

#include <cstdarg>
#include <cstdio>

bool color_enabled = false;

const char * clear_color = "\033[0m";

const char * color_lookup(Type type)
{
	switch(type)
	{
		case trace: return "\033[0m";
		case debug:	return "\033[0;34m";
		case info: 	return "\033[0;32m";
		case warn: 	return "\033[0;33m";
		case error:	return "\033[0;31m";
		case fatal:	return "\033[1;31m";
	}

	return ""; 
}

const char * type_string_lookup(Type type)
{
	switch(type)
	{
		case trace: return "trace";
		case debug:	return "debug";
		case info: 	return "info";
		case warn: 	return "warn";
		case error:	return "error";
		case fatal:	return "fatal";
	}

	return "";
}

int32 internal_printf(const char * title, Type type, const char * formatstring, std::va_list args)
{
	int32 ret = 0;

	const char * color = "";
	if(color_enabled) 
		color = color_lookup(type);

	ret += std::printf("%s[%s] ", color, title);
	ret += std::vprintf(formatstring, args);
	ret += std::printf("%s", clear_color);

	return ret;
}


void llama_console_enable_color(bool state)
{
	color_enabled = state;
}

bool llama_console_is_color_enable(void)
{
	return color_enabled;
}


int32 llama_console(Type type, const char * formatstring, ...)
{
	std::va_list args;
	va_start(args, formatstring);
	int32 ret = internal_printf(type_string_lookup(type), type, formatstring, args);
	va_end(args);

	return ret;
}

int32 llama_console(const char *title, Type type, const char * formatstring, ...)
{
	std::va_list args;
	va_start(args, formatstring);
	int32 ret = internal_printf(title, type, formatstring, args);
	va_end(args);

	return ret;
}

int32 llama_console(const char *title, const char * formatstring, ...)
{
	std::va_list args;
	va_start(args, formatstring);
	int32 ret = internal_printf(title, trace, formatstring, args);
	va_end(args);

	return ret;
}

int32 llama_console(const char * formatstring, ...)
{
	std::va_list args;
	va_start(args, formatstring);
	int32 ret = internal_printf(type_string_lookup(trace), trace, formatstring, args);
	va_end(args);

	return ret;
}
