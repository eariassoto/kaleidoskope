#include "pch.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "lexer.h"

int main()
{
	std::string input{ "extern abc\ndef abc\n123 + 12" };
	std::istringstream inputStream(input);

	kaleidoscope::Lexer lex;
	std::vector<kaleidoscope::Token*> vec2 = lex.readTokens(inputStream);
	for (const kaleidoscope::Token* tok : vec2)
	{
		std::cout << tok->toString() << ' ';
	}
	for (const kaleidoscope::Token* tok : vec2)
	{
		delete tok;
	}
}
