#include "Token.h"
#include <vector>
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
	std::istream& input_stream;
	std::vector<Token> tokens;
	bool full;
	Token buffer;

public:
	Token_stream(std::istream& input) :input_stream(input), full(0), buffer(_null) { }

	std::vector<Token> tokenize();
	Token get();
	void unget(Token t) { 
		buffer = t; 
		full = true; 
	}

	void ignore(Token_Type);
};