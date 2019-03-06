#include "tokens.h"

namespace kaleidoscope
{

	const char* tokenToString(kTokenType token)
	{
		switch (token)
		{
		case kTokenType::TOKENTYPE_EOF:
			return "EOF";
		case kTokenType::TOKENTYPE_DEF:
			return "DEF";
		case kTokenType::TOKENTYPE_EXTERN:
			return "EXTERN";
		case kTokenType::TOKENTYPE_IDENTIFIER:
			return "ID";
		case kTokenType::TOKENTYPE_NUMBER:
			return "NUM";
		case kTokenType::TOKENTYPE_INVALID:
			return "INVALID";
		}
		return "";
	}

	Token::Token(kTokenClass _tokenClass, kTokenType _tokenType)
		: mTokenClass{ _tokenClass },
		mTokenType { _tokenType } {}

	kTokenType Token::getTokenType() const { return mTokenType; }
	
	kTokenClass Token::getTokenClass() const { return mTokenClass; }

	SimpleToken::SimpleToken(kTokenType _tokenType) : Token(kTokenClass::TOKENCLASS_SIMPLE, _tokenType) {}

	const std::string SimpleToken::toString() const
	{
		std::string str{ "{ " };
		switch (mTokenType)
		{
		case kTokenType::TOKENTYPE_EOF:
			str += "EOF";
			break;
		case kTokenType::TOKENTYPE_DEF:
			str += "DEF";
			break;
		case kTokenType::TOKENTYPE_EXTERN:
			str += "EXTERN";
			break;
		case kTokenType::TOKENTYPE_INVALID:
			str += "INVALID";
			break;
		}
		str += " }";
		return str;
	}
	
	StringToken::StringToken(kTokenType _tokenType, const std::string &_string)
		: Token(kTokenClass::TOKENCLASS_STRING, _tokenType),
		mString{ _string } {}

	const std::string StringToken::toString() const
	{
		std::string str{ "{ " };
		switch (mTokenType)
		{
		case kTokenType::TOKENTYPE_IDENTIFIER:
			str += "ident: " + mString;
			break;
		}
		str += " }";
		return str;
	}
	
	NumberToken::NumberToken(kTokenType _tokenType, double _number)
		: Token(kTokenClass::TOKENCLASS_NUMBER, _tokenType),
		mNumber{ _number } {}

	const std::string NumberToken::toString() const
	{
		std::string str{ "{ " };
		switch (mTokenType)
		{
		case kTokenType::TOKENTYPE_NUMBER:
			str += "num: " + std::to_string(mNumber);
			break;
		}
		str += " }";
		return str;
	}

	CharToken::CharToken(kTokenType _tokenType, char _char)
		: Token(kTokenClass::TOKENCLASS_CHAR, _tokenType),
		mChar{ _char } {}

	const std::string CharToken::toString() const
	{
		std::string str{ "{ " };
		switch (mTokenType)
		{
		case kTokenType::TOKENTYPE_OPERATOR:
			str += "op: ";
			str += mChar;
			break;
		}
		str += " }";
		return str;
	}

	Token* TokenFactory::createSimpleToken(kTokenType _tokenType)
	{
		switch (_tokenType)
		{
		case kTokenType::TOKENTYPE_EOF:
		case kTokenType::TOKENTYPE_DEF:
		case kTokenType::TOKENTYPE_EXTERN:
		case kTokenType::TOKENTYPE_INVALID:
			return new SimpleToken(_tokenType);
		}
		return nullptr;
	}

	Token* TokenFactory::createStringToken(kTokenType _tokenType, const std::string& _string)
	{
		switch (_tokenType)
		{
		case kTokenType::TOKENTYPE_IDENTIFIER:
			return new StringToken(_tokenType, _string);
		}
		return nullptr;
	}

	Token* TokenFactory::createNumberToken(kTokenType _tokenType, double _number)
	{
		switch (_tokenType)
		{
		case kTokenType::TOKENTYPE_NUMBER:
			return new NumberToken(_tokenType, _number);
		}
		return nullptr;
	}

	Token* TokenFactory::createCharToken(kTokenType _tokenType, char _char)
	{
		switch (_tokenType)
		{
		case kTokenType::TOKENTYPE_OPERATOR:
			return new CharToken(_tokenType, _char);
		}
		return nullptr;
	}

} // namespace kaleidoscope
