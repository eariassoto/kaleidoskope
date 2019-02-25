#pragma once
#include <iostream>
#include <vector>
#include "tokens.h"

namespace kaleidoscope
{
	class Lexer
	{
	public:
		static std::vector<kTokenType> readTokens(std::istream& input);
		static const char* tokenToString(kTokenType token);
	private:
		static kTokenType getToken(std::istream& input);
	};

} // namespace kaleidoscope