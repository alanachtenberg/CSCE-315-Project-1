#include "Token_Stream.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//TODO: add support for literals as string, int, or double
//TODO: change multi-word combinations (i.e. VALUES FROM) to be a single token 


//Each character input is turned into a token, using Token_stream::get
Token Token_stream::get() {
	Token curr_token(_null);
	char ch;
	string s;
	bool negative = false;

	if (!unget_tokens.empty()) {
		curr_token = unget_tokens.top();
		unget_tokens.pop();

		return curr_token;
	}

	if (*input_stream >> ch) {
		switch (ch) {
		case '(': curr_token = Token(_lpar); break;
		case ')': curr_token = Token(_rpar); break;
		case '+': curr_token = Token(_plus); break;
		case '-': 
			//char following minus is a number, so we are reading a negative number
			if (isdigit(input_stream->peek())) {
				s = "";
				s += ch;
				while (input_stream->get(ch) && (isdigit(ch) || ch == '.')) {
					s += ch;
				}

				input_stream->unget();
				stringstream ss(s);
				//determine if the number is a float or integer
				if (s.find('.') == string::npos) {
					int int_val;
					ss >> int_val;
					curr_token = Token(_int_num, int_val);
				}
				else {
					float float_val;
					ss >> float_val;
					curr_token = Token(_float_num, float_val);
				}
				break;
			}
			//if we don't have a negative number, then its the operator
			else {
				curr_token = Token(_minus); 
				break;
			}
		case '*': curr_token = Token(_multiply); break;
		case '/': curr_token = Token(_divide); break;
		case '%': curr_token = Token(_mod); break;
		case ';': curr_token = Token(_semicolon); break;
		case ',': curr_token = Token(_comma); break;
		case '"': 
			getline(*input_stream, s, '\"');
			if (input_stream->eof()) {
				BadTokenException ex("Bad Token: missing end quotation in literal");
				throw ex;
			}
			else {
				curr_token = Token(_literal, s);
				break;
			}
		case '<':
			input_stream->get(ch);
			if (ch == '-') {
				curr_token = Token(_assign, "<-");
			}
			else if (ch == '=') {
				curr_token = Token(_less_eq, "<=");
			}
			else {
				curr_token = Token(_less, "<");
			}
			break;
		case '>':
			input_stream->get(ch);
			if (ch == '=') {
				curr_token = Token(_greater_eq, ">=");
			}
			else {
				curr_token = Token(_greater, ">");
			}
			break;
		case '=':
			input_stream->get(ch);
			if (ch == '=') {
				curr_token = Token(_equals, "==");
			}
			else {
				curr_token = Token(_assign_eq, "=");
			}
			break;
		case '!':
			input_stream->get(ch);
			if (ch == '=') {
				curr_token = Token(_not_eq, "!=");
			}
			break;
		case '&':
			input_stream->get(ch);
			if (ch == '&') {
				curr_token = Token(_and, "&&");
			}
			break;
		case '|':
			input_stream->get(ch);
			if (ch == '|') {
				curr_token = Token(_or, "||");
			}
			break;
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
		case '9': { //we are reading some kind of number
			s = "";
			s += ch;
			while (input_stream->get(ch) && (isdigit(ch) || ch == '.')) {
				s += ch;
			}
					  
			input_stream->unget();
			stringstream ss(s);
			//determine if the number is a float or integer
			if (s.find('.') == string::npos) {
				int int_val;
				ss >> int_val;
				curr_token = Token(_int_num, int_val);
			}
			else {
				float float_val;
				ss >> float_val;
				curr_token = Token(_float_num, float_val);
			}
			break;
		}
		default:
			if (isalpha(ch)) {
				s = "";
				s += ch;
				while (input_stream->get(ch) && (isalpha(ch) || ch == '_')) {
					s += ch;
				}
				input_stream->unget();
				//transform(s.begin(), s.end(), s.begin(), ::tolower); //convert string to lowercase

				//reserved words
				if (s == "CREATE")			curr_token = Token(_create);
				else if (s == "INSERT")		curr_token = Token(_insert);
				else if (s == "select")		curr_token = Token(_select);
				else if (s == "project")	curr_token = Token(_project);
				else if (s == "SHOW")		curr_token = Token(_show);
				else if (s == "rename")		curr_token = Token(_rename);

				else if (s == "INTO")		curr_token = Token(_into);
				else if (s == "TABLE")		curr_token = Token(_table);
				else if (s == "VALUES")		curr_token = Token(_values);
				else if (s == "FROM")		curr_token = Token(_from);
				else if (s == "PRIMARY")	curr_token = Token(_primary);
				else if (s == "KEY")		curr_token = Token(_key);

				else if (s == "RELATION")	curr_token = Token(_relation);
				else if (s == "WRITE")		curr_token = Token(_write);
				else if (s == "OPEN")		curr_token = Token(_open);
				else if (s == "CLOSE")		curr_token = Token(_close);
				else if (s == "DELTE")		curr_token = Token(_delete);
				else if (s == "UPDATE")		curr_token = Token(_update);
				else if (s == "SET")		curr_token = Token(_set);
				else if (s == "WHERE")		curr_token = Token(_where);

				else if (s == "FLOAT")		curr_token = Token(_float_type);
				else if (s == "INTEGER")	curr_token = Token(_int_type);
				else if (s == "CHAR")		curr_token = Token(_char);
				else if (s == "VARCHAR") {
					char lpar, rpar;
					int size;
					*input_stream >> lpar;
					if (lpar == '(') {
						*input_stream >> size >> rpar;
						if (rpar == ')') {
							curr_token = Token(_varchar, size);
						}
					}
				}
				else if (s == "EXIT")		curr_token = Token(_exit_program);
				else						curr_token = Token(_identifier, s);
				break;
			}
		}
		if (curr_token.get_type() != _null) {
			tokens.push_back(curr_token);
			return curr_token;
		}
		else {
			BadTokenException ex("Bad Token: " + s);
			throw ex;
		}
	}
	else {
		BadTokenException ex("Attempt to read from empty stream");
		throw ex;
	}
}