#include "Token.h"

class Token_stream {
private:
	std::istream& input_stream;
	bool full;
	Token buffer;

public:
	Token_stream(std::istream& input) :input_stream(input), full(0), buffer(_null) { }

	Token get();
	void unget(Token t) { 
		buffer = t; 
		full = true; 
	}

	void ignore(Token_Type);
};