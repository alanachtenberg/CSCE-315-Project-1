#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "Token.h"
#include <vector>
#include <stack>
#include <sstream>

inline bool isspecial(char ch) {
	return (
		   ch == '_'
		|| ch == '='
		|| ch == '!'
		|| ch == '&'
		|| ch == '|'
		|| ch == '>'
		|| ch == '<'
		|| ch == '-');
}

class Token_stream {
private:
	std::istream* input_stream;
	std::vector<Token> tokens;
	std::stack<Token> unget_tokens;

public:
	Token_stream(std::string input) { 
		input_stream = new std::istringstream(input);
	}

	Token_stream(std::istream *input) :input_stream(input) { }

	~Token_stream() {
		delete input_stream;
	}

	std::vector<Token> tokenize();
	Token get();
	void unget(Token t) { 
		unget_tokens.push(t);
	}

	void ignore(Token_Type);
};

#endif