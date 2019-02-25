#include "lexer.h"

namespace kaleidoscope
{
	// TODO: remove this when Token are treated as objects
	static std::string identifierStr;
	static double numVal;

	const char* Lexer::tokenToString(kTokenType token)
	{
		switch (token)
		{
		case kTokenType::TOKEN_EOF:
			return "EOF";
		case kTokenType::TOKEN_DEF:
			return "DEF";
		case kTokenType::TOKEN_EXTERN:
			return "EXTERN";
		case kTokenType::TOKEN_IDENTIFIER:
			return "ID";
		case kTokenType::TOKEN_NUMBER:
			return "NUM";
		case kTokenType::TOKEN_INVALID:
			return "INVALID";
		}
		return "";
	}

	kTokenType Lexer::getToken(std::istream& input)
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
				return kTokenType::TOKEN_DEF;
			if (identifierStr == "extern")
				return kTokenType::TOKEN_EXTERN;
			return kTokenType::TOKEN_IDENTIFIER;
		}
		else if (isdigit(lastChar) || lastChar == '.')
		{   // Number: [0-9.]+
			std::string NumStr;
			do {
				numVal += lastChar;
				lastChar = input.get();
			} while (isdigit(lastChar) || lastChar == '.');

			numVal = strtod(NumStr.c_str(), 0);
			return kTokenType::TOKEN_NUMBER;
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
			return kTokenType::TOKEN_EOF;
		}
		return kTokenType::TOKEN_INVALID;
	}

	std::vector<kTokenType> Lexer::readTokens(std::istream& input)
	{
		std::vector<kTokenType> tokens;
		kTokenType currentToken = kTokenType::TOKEN_EOF;
		do
		{
			currentToken = getToken(input);
			tokens.push_back(currentToken);
		} while (currentToken != kTokenType::TOKEN_EOF);
		return tokens;
	}

} // namespace kaleidoscope