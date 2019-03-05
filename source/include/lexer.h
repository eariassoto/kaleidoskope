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
		Token* parseAlphaToken(std::istream& input);
		Token* parseNumericToken(std::istream& input);
		Token* getToken(std::istream& input);
	};

} // namespace kaleidoscope