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
		virtual const std::string toString() const = 0;
	protected:
		Token(kTokenClass _tokenClass, kTokenType _tokenType);

		kTokenType mTokenType;
	private:
		kTokenClass mTokenClass;
	};

	class SimpleToken : public Token
	{
	public:
		SimpleToken(kTokenType _tokenType);
		const std::string toString() const;
	};

	class StringToken : public Token
	{
	public:
		StringToken(kTokenType _tokenType, const std::string &_string);
		const std::string toString() const;
	private:
		std::string mString;
	};

	class NumberToken : public Token
	{
	public:
		NumberToken(kTokenType _tokenType, double _number);
		const std::string toString() const;
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