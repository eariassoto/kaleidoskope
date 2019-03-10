#include "lexer.h"
#include <unordered_map>

namespace kaleidoscope
{
	static std::unordered_map<char, kTokenType> symbolTokenMap{
		{'+', kTokenType::TOKENTYPE_ADD},
		{'-', kTokenType::TOKENTYPE_SUB},
		{'*', kTokenType::TOKENTYPE_MUL},
		{'/', kTokenType::TOKENTYPE_DIV},
	};

	Token* Lexer::parseAlphaToken(const std::string& token)
	{
		if (token.compare("def") == 0)
			return TokenFactory::createSimpleToken(kTokenType::TOKENTYPE_DEF);
		if (token.compare("extern") == 0)
			return TokenFactory::createSimpleToken(kTokenType::TOKENTYPE_EXTERN);
		return TokenFactory::createStringToken(kTokenType::TOKENTYPE_IDENTIFIER, token);
		return nullptr; // todo: return error token
	}

	Token* Lexer::parseNumericToken(const std::string& token)
	{
		double number = .0;

		try {
			number = strtod(token.c_str(), 0);
		}
		catch (const std::exception& /*e*/) {
			return nullptr;
		}
		return TokenFactory::createNumberToken(kTokenType::TOKENTYPE_NUMBER, number);
	}

	Token* Lexer::parseCharToken(char token)
	{
		auto it = symbolTokenMap.find(token);
		if (it == symbolTokenMap.end())
			return nullptr;

		return TokenFactory::createCharToken(it->second, it->first);
	}

	std::vector<Token*> Lexer::readTokens(std::istream& input)
	{
		std::vector<Token*> tokens;
		std::string stringToken;
		stringToken.reserve(512);

		int currentChar = ' ';
		do
		{
			while (isspace(currentChar))
				currentChar = input.get();

			if (currentChar == '#')
			{
				while (currentChar != '\n' || currentChar == EOF)
					currentChar = input.get();
			}
			else
			{
				if (isalpha(currentChar))
				{
					stringToken.clear();
					do
					{
						stringToken += currentChar;
						currentChar = input.get();
					} while (isalnum(currentChar));

					Token* token = parseAlphaToken(stringToken);
					if (token)
						tokens.push_back(token);
				}
				else if (isdigit(currentChar))
				{
					// todo check numbers that start with .
					// todo allow only one . in the token
					stringToken.clear();
					do
					{
						stringToken += currentChar;
						currentChar = input.get();
					} while (isdigit(currentChar) || currentChar == '.');

					Token* token = parseNumericToken(stringToken);
					if (token)
						tokens.push_back(token);
				}
				else
				{
					Token* token = parseCharToken(currentChar);
					if (token)
						tokens.push_back(token);
				}
				currentChar = input.get();
			}
		} while (currentChar != EOF);
		return tokens;
	}

} // namespace kaleidoscope