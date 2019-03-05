#include "lexer.h"

namespace kaleidoscope
{
	Token* Lexer::parseAlphaToken(std::istream& input)
	{
		int currentChar = ' ';
		std::string identifierStr;

		while (isalnum((currentChar = input.get())))
			identifierStr += currentChar;

		if (identifierStr == "def")
			return TokenFactory::createSimpleToken(kTokenType::TOKEN_DEF);
		if (identifierStr == "extern")
			return TokenFactory::createSimpleToken(kTokenType::TOKEN_EXTERN);
		return TokenFactory::createStringToken(kTokenType::TOKEN_IDENTIFIER, identifierStr);

		return nullptr;
	}

	Token* Lexer::parseNumericToken(std::istream& input)
	{
		int currentChar = input.get();
		std::string numStr;
		do {
			numStr += currentChar;
			currentChar = input.get();
		} while (isdigit(currentChar) || currentChar == '.');

		return TokenFactory::createNumberToken(kTokenType::TOKEN_NUMBER, strtod(numStr.c_str(), 0));
	}

	Token* Lexer::getToken(std::istream& input)
	{
		while (isspace(input.peek()))
			input.get();
	
		int lastChar = input.peek();
		if (isalpha(lastChar))
		{ // identifier: [a-zA-Z][a-zA-Z0-9]*
			return parseAlphaToken(input);
		}
		else if (isdigit(lastChar) || lastChar == '.')
		{   // Number: [0-9.]+
			return parseNumericToken(input);
		}
		else if (lastChar == '#')
		{
			// Comment until end of line.
			// TODO: check multiple # chars
			do
				lastChar = input.get();
			while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

			if (lastChar != EOF)
				return getToken(input); // TODO: avoid recursivity
		}
		else if (lastChar == EOF)
		{
			return TokenFactory::createSimpleToken(kTokenType::TOKEN_EOF);
		}
		return TokenFactory::createSimpleToken(kTokenType::TOKEN_INVALID);
	}

	std::vector<Token*> Lexer::readTokens(std::istream& input)
	{
		std::vector<Token*> tokens;
		Token* currentToken{ nullptr };
		do
		{
			currentToken = getToken(input);
			tokens.push_back(currentToken);
		} while (currentToken && currentToken->getTokenType() != kTokenType::TOKEN_EOF);
		return tokens;
	}

} // namespace kaleidoscope