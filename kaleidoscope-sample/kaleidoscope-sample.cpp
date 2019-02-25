#include "pch.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "lexer.h"

int main()
{
	std::string input{ "extern abc\ndef abc" };
	std::istringstream inputStream(input);

	std::vector<kaleidoscope::kTokenType> vec = kaleidoscope::Lexer::readTokens(inputStream);
	for (const kaleidoscope::kTokenType tok : vec)
	{
		std::cout << kaleidoscope::Lexer::tokenToString(tok) << ' ';
	}
}
