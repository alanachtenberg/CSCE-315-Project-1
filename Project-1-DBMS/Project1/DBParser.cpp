#include "DBParser.h"

bool DBParser::program() {
	return query() || command();
}

//unfinished
bool DBParser::query() {
	return false; //just to let me build for now
}

bool DBParser::command() {
	Token lpar_token, rpar_token, semicolon_token;

	lpar_token = ts.get();

	if (lpar_token.get_type() == _lpar) {
		bool value = 
			open_cmd()
		|| close_cmd()
		|| write_cmd()
		||	exit_cmd()
		||	show_cmd()
		|| create_cmd()
		|| update_cmd()
		|| insert_cmd()
		|| delete_cmd();

		rpar_token = ts.get();

		if (rpar_token.get_type() == _rpar) {
			semicolon_token = ts.get();
			if (semicolon_token.get_type() == _semicolon) {
				return value;
			}
			else {
				ts.unget(semicolon_token);
				ts.unget(rpar_token);
				ts.unget(lpar_token);
				return false;
			}
		}
		else {
			ts.unget(rpar_token);
			ts.unget(lpar_token);
			return false;
		}
	}
	else {
		ts.unget(lpar_token);
		return false;
	}
}

bool DBParser::open_cmd() {
	Token open_token = ts.get();

	if (open_token.get_type() == _open) {
		return relation_name();
	}
	else {
		ts.unget(open_token);
		return false;
	}
}

bool DBParser::close_cmd() {
	Token close_token = ts.get();

	if (close_token.get_type() == _close) {
		return relation_name();
	}
	else {
		ts.unget(close_token);
		return false;
	}
}

bool DBParser::write_cmd() {
	Token write_token = ts.get();

	if (write_token.get_type() == _write) {
		return relation_name();
	}
	else {
		ts.unget(write_token);
		return false;
	}
}

bool DBParser::exit_cmd() {
	Token exit_token = ts.get();

	if (exit_token.get_type() == _exit_program) {
		return true;
	}
	else {
		ts.unget(exit_token);
		return false;
	}
}

bool DBParser::show_cmd() {
	Token show_token = ts.get();

	if (show_token.get_type() == _show) {
		return atomic_expr();
	}
	else {
		ts.unget(show_token);
		return false;
	}
}

bool DBParser::create_cmd() {
	Token create_token = ts.get();
	Token table_token = ts.get();

	if (create_token.get_type() == _create && table_token.get_type() == _table) {
		bool value = relation_name();

		Token lpar_token = ts.get();
		if (value && lpar_token.get_type() == _lpar) {

			value = typed_attribute_list();

			Token rpar_token = ts.get();
			Token primary_token = ts.get();
			Token key_token = ts.get();
			Token llpar_token = ts.get();
			if (value && rpar_token.get_type() == _rpar &&
				primary_token.get_type() == _primary &&
				key_token.get_type() == _key &&
				llpar_token.get_type() == _lpar) {

				value = attribute_list();

				Token rrpar_token = ts.get();
				Token semicolon_token = ts.get();
				if (value && rrpar_token.get_type() == _rpar && 
					semicolon_token.get_type() == _semicolon) {
					return true;
				}
				else {
					ts.unget(semicolon_token);
					ts.unget(rrpar_token);
					ts.unget(llpar_token);
					ts.unget(key_token);
					ts.unget(primary_token);
					ts.unget(rpar_token);
					ts.unget(lpar_token);
					ts.unget(table_token);
					ts.unget(create_token);

					return false;
				}
			}
			else {
				ts.unget(llpar_token);
				ts.unget(key_token);
				ts.unget(primary_token);
				ts.unget(rpar_token);	
				ts.unget(lpar_token);
				ts.unget(table_token);
				ts.unget(create_token);

				return false;
			}
		}
		else {
			ts.unget(lpar_token);
			ts.unget(table_token);
			ts.unget(create_token);

			return false;
		}
	}
	else {
		ts.unget(table_token);
		ts.unget(create_token);

		return false;
	}
}

//unfinished
bool DBParser::update_cmd() {
	return false;
}

//unfinished
bool DBParser::insert_cmd() {
	return false;
}

//unfinished
bool DBParser::delete_cmd() {
	return false;
}

//Data structures
//------------------------------------------------------------------------------
bool DBParser::relation_name() {
	Token relation_name_token = ts.get();
	if (relation_name_token.get_type() == _identifier) {
		return true;
	}
	else {
		ts.unget(relation_name_token);
		return false;
	}
}

//unfinished
bool DBParser::expr() {
	return false;
}

bool DBParser::atomic_expr() {
	Token lpar_token, rpar_token;

	lpar_token = ts.get();

	if (lpar_token.get_type() == _lpar) {
		bool value = expr();
		rpar_token = ts.get();

		if (rpar_token.get_type() == _rpar) {
			return value;
		}
		else {
			ts.unget(rpar_token);
			ts.unget(lpar_token);
			return false;
		}
	}
	else {
		ts.unget(lpar_token);
		return false;
	}
}

bool DBParser::attribute_name() {
	Token identifier_token = ts.get();
	if (identifier_token.get_type() == _identifier) {
		return true;
	}
	else {
		ts.unget(identifier_token);
		return false;
	}
}

//change to use integer, identifier functions
bool DBParser::type() {
	Token integer_token = ts.get();
	if (integer_token.get_type() == _number) {
		return true;
	}
	else if (integer_token.get_type() == _varchar) {
		Token lpar = ts.get();
		Token integer_token_2 = ts.get();
		Token rpar = ts.get();
		if (lpar.get_type() == _lpar && 
			integer_token_2.get_type() == _number &&
			rpar.get_type() == _rpar) {
			return true;
		}
		else {
			ts.unget(rpar);
			ts.unget(integer_token_2);
			ts.unget(lpar);
			ts.unget(integer_token);

			return false;
		}
	}
	else {
		ts.unget(integer_token);

		return false;
	}
}

//unfinished
bool DBParser::typed_attribute_list() {
	if (attribute_name()) {
		if (type()) {
		
		}
	}
	

	return false;
}

//unfinished
