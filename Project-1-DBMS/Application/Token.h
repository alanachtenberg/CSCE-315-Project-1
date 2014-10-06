#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <fstream>

enum Token_Type {
	_lpar, _rpar, _assign, _assign_eq, _comma, _semicolon,
	_plus, _minus, _multiply, _divide, _mod,
	_equals, _not_eq, _less, _less_eq, _greater, _greater_eq,
	_and, _or,
	_create, _insert, _select, _project, _show, _rename,
	_into, _table, _values, _from, _primary, _key,
	_relation, _write, _open, _close, _delete, _update, _set, _where,
	_int_type, _int_num, _float_type, _float_num, _varchar, _char, _literal, _identifier,
	_exit_program, _null
};

std::string Token_Type_Name[];

struct Token {
private:
	Token_Type type;
	double value;
	std::string name;

public:

	Token()									:type(_null),	value(0),	name("") { }
	Token(Token_Type type)					:type(type),	value(0),	name("") { }
	Token(Token_Type type, double val)		:type(type),	value(val),	name("") { }
	Token(Token_Type type, std::string s)	:type(type),	value(0),	name(s) { }

	Token_Type get_type() {
		return type;
	}

	std::string get_type_name() {
		return Token_Type_Name[type];
	}

	std::string get_name() {
		return name;
	}

	double get_value() {
		return value;
	}
};

class BadTokenException : public std::exception {
	std::string msg;
public:
	BadTokenException(std::string s) : msg(s) {}

	virtual const char* what() const throw() {
		return msg.c_str();
	}
};

#endif