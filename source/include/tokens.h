#pragma once
#include <string>

namespace kaleidoscope
{
	enum class kTokenType
	{
		TOKEN_EOF,
		TOKEN_DEF,
		TOKEN_EXTERN,
		TOKEN_IDENTIFIER,
		TOKEN_NUMBER,
		TOKEN_INVALID
	};

	enum class kTokenClass
	{
		TOKENTYPE_STRING,
		TOKENTYPE_NUMBER,
		TOKENTYPE_SIMPLE
	};

	class Token
	{
	public:
		kTokenClass getTokenClass() const;
		kTokenType getTokenType() const;
	protected:
		Token(kTokenClass _tokenClass, kTokenType _tokenType);
	private:
		kTokenClass mTokenClass;
		kTokenType mTokenType;
	};

	class SimpleToken : public Token
	{
	public:
		SimpleToken(kTokenType _tokenType);
	};

	class StringToken : public Token
	{
	public:
		StringToken(kTokenType _tokenType, const std::string &_string);
	private:
		std::string mString;
	};

	class NumberToken : public Token
	{
	public:
		NumberToken(kTokenType _tokenType, double _number);
	private:
		double mNumber;
	};

	class TokenFactory
	{
	public:
		static Token* createSimpleToken(kTokenType _tokenType);
		static Token* createStringToken(kTokenType _tokenType, const std::string& _string);
		static Token* createNumberToken(kTokenType _tokenType, double _number);
	};
} // namespace kaleidoscope