#include <iostream>

#include "debug.h"

Debug::DebugStream::DebugStream(std::string header, std::string text_color):
	std::ostream(this), new_line(true), header(header), text_color(text_color) {}

std::streambuf::int_type Debug::DebugStream::overflow(std::streambuf::int_type c){

	std::cout << text_color;

	if(new_line){
		std::cout << header;
		new_line = false;
	}

	std::cout << (char)c;
	std::cout << "\033[0m";

	new_line = (c == '\n');

	return 0;
}
