#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <iostream>

namespace Debug{

	class DebugStream : std::streambuf, public std::ostream{
		public:
			DebugStream(std::string header, std::string text_color);
			std::streambuf::int_type overflow(std::streambuf::int_type c) override;
		private:
			bool new_line;
			std::string header, text_color;
	};


	static DebugStream Info   ("[INFO] ", "\033[1;37m");
	static DebugStream Warning("[WARN] ", "\033[1;33m");
	static DebugStream Error  ("[ERRO] ", "\033[1;31m");
};

#endif
