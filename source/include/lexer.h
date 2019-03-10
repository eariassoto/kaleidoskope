#pragma once
#include <iostream>
#include <vector>
#include "tokens.h"

namespace kaleidoscope
{
	class Lexer
	{
	public:
		std::vector<Token*> readTokens(std::istream& input);

	private:
		Token* parseAlphaToken(const std::string& token);
		Token* parseNumericToken(const std::string& token);
		Token* parseCharToken(char token);
	};

} // namespace kaleidoscope