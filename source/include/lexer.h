#pragma once
#include <iostream>
#include <vector>

namespace kaleidoscope
{
	enum class kTokens
	{
		TOKEN_EOF,
		TOKEN_DEF,
		TOKEN_EXTERN,
		TOKEN_IDENTIFIER,
		TOKEN_NUMBER,
		TOKEN_INVALID
	};

	class Lexer
	{
	public:
		static std::vector<kTokens> readTokens(std::istream& input);
		static const char* tokenToString(kTokens token);
	private:
		static kTokens getToken(std::istream& input);
	};

} // namespace kaleidoscope