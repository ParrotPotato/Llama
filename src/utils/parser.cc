#include "parser.hh"

char * llama_parser_eat_white_space(char * ptr)
{
	while(*ptr == ' ' || *ptr == '\n' || *ptr == '\r' || *ptr == '\t') ptr++;
	return ptr;
}

