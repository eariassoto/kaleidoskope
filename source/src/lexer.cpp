#include "lexer.h"

namespace kaleidoscope
{
	bool isOperator(char ch)
	{
		return
			ch == '+'
			|| ch == '-'
			|| ch == '*'
			|| ch == '/';
	}

	Token* Lexer::parseAlphaToken(std::istream& input)
	{
		std::string identifierStr{ (char)input.get() };

		// todo fix this: read token should consume the entire char seq
		while (isalnum(input.peek()))
		{
			identifierStr += input.get();
		}

		if (identifierStr == "def")
			return TokenFactory::createSimpleToken(kTokenType::TOKENTYPE_DEF);
		if (identifierStr == "extern")
			return TokenFactory::createSimpleToken(kTokenType::TOKENTYPE_EXTERN);
		return TokenFactory::createStringToken(kTokenType::TOKENTYPE_IDENTIFIER, identifierStr);

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

		return TokenFactory::createNumberToken(kTokenType::TOKENTYPE_NUMBER, strtod(numStr.c_str(), 0));
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
		else if (isOperator(lastChar))
			return TokenFactory::createCharToken(kTokenType::TOKENTYPE_OPERATOR, input.get()); // todo: fix this get
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
			return TokenFactory::createSimpleToken(kTokenType::TOKENTYPE_EOF);
		}
		// todo fix this:
		// consume char
		input.get();
		return TokenFactory::createSimpleToken(kTokenType::TOKENTYPE_INVALID);
	}

	std::vector<Token*> Lexer::readTokens(std::istream& input)
	{
		std::vector<Token*> tokens;
		Token* currentToken{ nullptr };
		do
		{
			currentToken = getToken(input);
			tokens.push_back(currentToken);
		} while (currentToken && currentToken->getTokenType() != kTokenType::TOKENTYPE_EOF);
		return tokens;
	}

} // namespace kaleidoscope