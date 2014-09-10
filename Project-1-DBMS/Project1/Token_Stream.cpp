#include <algorithm>
#include <iostream>
#include "Token_Stream.h"

using namespace std;

//Each character input is turned into a token, using Token_stream::get
Token Token_stream::get() {
	if (full) { 
		full = false; 
		return buffer; 
	}

	char ch;
	input_stream >> ch;

	switch (ch) {
	case '(': return Token(_lpar);
	case ')': return Token(_rpar);
	case '+': return Token(_plus);
	case '-': return Token(_minus);
	case '*': return Token(_multiply);
	case '/': return Token(_divide);
	case '%': return Token(_mod);
	case ';': return Token(_semicolon);
	case ',': return Token(_comma);
	case '<': {
		char c2;
		input_stream >> c2;
		if (c2 == '-') return Token(_assign);
		else if (c2 == '=') return Token(_less_eq);
		else {
			input_stream.unget();
			return Token(_less);
		}
	}
	case '>': {
		char c2;
		input_stream >> c2;
		if (c2 == '=') return Token(_greater_eq);
		else {
			input_stream.unget();
			return Token(_greater);
		}
	}
	case '!': {
		char c2;
		input_stream >> c2;
		if (c2 == '=') return Token(_not_eq);
		else {
			BadTokenException ex("bad token");
			throw ex;
		}
	}
	case '=': {
		char c2;
		input_stream >> c2;
		if (c2 == '=') return Token(_equals);
		else {
			BadTokenException ex("bad token");
			throw ex;
		}
	}
	case '&': {
		char c2;
		input_stream >> c2;
		if (c2 == '&') return Token(_and);
		else {
			BadTokenException ex("bad token");
			throw ex;
		}
	}
	case '|': {
		char c2;
		input_stream >> c2;
		if (c2 == '|') return Token(_or);
		else {
			BadTokenException ex("bad token");
			throw ex;
		}
	}
	case '"': return Token(_quotation);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {	
		input_stream.unget();
		double val;
		input_stream >> val;
		return Token(_number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (input_stream.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) {
				s += ch;
			}
			input_stream.unget();
			transform(s.begin(), s.end(), s.begin(), ::tolower); //convert string to lowercase

			//reserved words
			if (s == "create") return Token(_create);
			if (s == "insert") return Token(_insert);
			if (s == "select") return Token(_select);
			if (s == "show") return Token(_show);
			if (s == "rename") return Token(_rename);

			if (s == "into") return Token(_into);
			if (s == "table") return Token(_table);
			if (s == "values") return Token(_values);
			if (s == "from") return Token(_from);
			if (s == "primary") return Token(_primary);
			if (s == "key") return Token(_key);

			if (s == "relation") return Token(_relation);
			if (s == "write") return Token(_write);
			if (s == "close") return Token(_close);

			if (s == "integer") return Token(_integer);
			if (s == "varchar") return Token(_varchar);
			if (s == "char") return Token(_char);
			if (s == "float") return Token(_float);

			if (s == "exit") return Token(_exit_program);

			return Token(_identifier, s);
		}
		BadTokenException ex("bad token");
		throw ex;
	}
	return Token(_null);
}

//Allows for a bad token to be ignored and not interfere with execution
void Token_stream::ignore(Token_Type c) {
	if (full && c == buffer.get_type()) {
		full = false;
		return;
	}
	full = false;

	return;
}