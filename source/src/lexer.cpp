#include "lexer.h"

namespace kaleidoscope
{
	// TODO: remove this when Token are treated as objects
	static std::string identifierStr;
	static double numVal;

	const char* Lexer::tokenToString(kTokens token)
	{
		switch (token)
		{
		case kTokens::TOKEN_EOF:
			return "EOF";
		case kTokens::TOKEN_DEF:
			return "DEF";
		case kTokens::TOKEN_EXTERN:
			return "EXTERN";
		case kTokens::TOKEN_IDENTIFIER:
			return "ID";
		case kTokens::TOKEN_NUMBER:
			return "NUM";
		case kTokens::TOKEN_INVALID:
			return "INVALID";
		}
		return "";
	}

	kTokens Lexer::getToken(std::istream& input)
	{
		static int lastChar = ' ';
		while (isspace(lastChar))
			lastChar = input.get();

		if (isalpha(lastChar))
		{ // identifier: [a-zA-Z][a-zA-Z0-9]*
			identifierStr = lastChar;
			while (isalnum((lastChar = input.get())))
				identifierStr += lastChar;

			if (identifierStr == "def")
				return kTokens::TOKEN_DEF;
			if (identifierStr == "extern")
				return kTokens::TOKEN_EXTERN;
			return kTokens::TOKEN_IDENTIFIER;
		}
		else if (isdigit(lastChar) || lastChar == '.')
		{   // Number: [0-9.]+
			std::string NumStr;
			do {
				numVal += lastChar;
				lastChar = input.get();
			} while (isdigit(lastChar) || lastChar == '.');

			numVal = strtod(NumStr.c_str(), 0);
			return kTokens::TOKEN_NUMBER;
		}
		else if (lastChar == '#')
		{
			// Comment until end of line.
			// TODO: check multiple # chars
			do
				lastChar = input.get();
			while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

			if (lastChar != EOF)
				return getToken(input);
		}
		else if (lastChar == EOF)
		{
			return kTokens::TOKEN_EOF;
		}
		return kTokens::TOKEN_INVALID;
	}

	std::vector<kTokens> Lexer::readTokens(std::istream& input)
	{
		std::vector<kTokens> tokens;
		kTokens currentToken = kTokens::TOKEN_EOF;
		do
		{
			currentToken = getToken(input);
			tokens.push_back(currentToken);
		} while (currentToken != kTokens::TOKEN_EOF);
		return tokens;
	}

} // namespace kaleidoscope