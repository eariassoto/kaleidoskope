#include "tokens.h"

namespace kaleidoscope
{

	const char* tokenToString(kTokenType token)
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

	const std::string SimpleToken::toString() const
	{
		std::string str{"{ "};
		switch (mTokenType)
		{
		case kTokenType::TOKEN_EOF:
			str += "EOF";
			break;
		case kTokenType::TOKEN_DEF:
			str += "DEF";
			break;
		case kTokenType::TOKEN_EXTERN:
			str += "EXTERN";
			break;
		case kTokenType::TOKEN_INVALID:
			str += "INVALID";
			break;
		}
		str += " }";
		return str;
	}

	const std::string StringToken::toString() const
	{
		std::string str{ "{ " };
		switch (mTokenType)
		{
		case kTokenType::TOKEN_IDENTIFIER:
			str += "ident: " + mString;
			break;
		}
		str += " }";
		return str;
	}

	const std::string NumberToken::toString() const
	{
		std::string str{ "{ " };
		switch (mTokenType)
		{
		case kTokenType::TOKEN_NUMBER:
			str += "num: " + std::to_string(mNumber);
			break;
		}
		str += " }";
		return str;
	}

	Token::Token(kTokenClass _tokenClass, kTokenType _tokenType)
		: mTokenClass{ _tokenClass },
		mTokenType { _tokenType } {}

	kTokenType Token::getTokenType() const { return mTokenType; }
	
	kTokenClass Token::getTokenClass() const { return mTokenClass; }

	SimpleToken::SimpleToken(kTokenType _tokenType) : Token(kTokenClass::TOKENTYPE_SIMPLE, _tokenType) {}
	
	StringToken::StringToken(kTokenType _tokenType, const std::string &_string)
		: Token(kTokenClass::TOKENTYPE_STRING, _tokenType),
		mString{ _string } {}
	
	NumberToken::NumberToken(kTokenType _tokenType, double _number)
		: Token(kTokenClass::TOKENTYPE_NUMBER, _tokenType),
		mNumber{ _number } {}

	Token* TokenFactory::createSimpleToken(kTokenType _tokenType)
	{
		switch (_tokenType)
		{
		case kTokenType::TOKEN_EOF:
		case kTokenType::TOKEN_DEF:
		case kTokenType::TOKEN_EXTERN:
		case kTokenType::TOKEN_INVALID:
			return new SimpleToken(_tokenType);
		}
		return nullptr;
	}

	Token* TokenFactory::createStringToken(kTokenType _tokenType, const std::string& _string)
	{
		switch (_tokenType)
		{
		case kTokenType::TOKEN_IDENTIFIER:
			return new StringToken(_tokenType, _string);
		}
		return nullptr;
	}

	Token* TokenFactory::createNumberToken(kTokenType _tokenType, double _number)
	{
		switch (_tokenType)
		{
		case kTokenType::TOKEN_NUMBER:
			return new NumberToken(_tokenType, _number);
		}
		return nullptr;
	}

} // namespace kaleidoscope
