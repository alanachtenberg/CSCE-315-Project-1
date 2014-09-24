#include "DBParser.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
//terrible hack to redirect console output to file
ofstream ofs("output.txt");
#define cout ofs
*/

bool DBParser::execute_query(string query) {
	ts = new Token_stream(query);

	bool valid = program();
	delete ts;
	return valid;
}

void DBParser::execute_file(string filename) {
	ifstream ifs(filename);
	string line;
	int valid = 0, invalid = 0, line_no = 0;

	cout << "EXECUTING FILE " << filename << ":";
	while (getline(ifs, line)) {
		line_no++;
		if (line.size() > 0) {
			try {
				bool works = execute_query(line);


				if (works) {
					valid++;
				}
				else {
					cout << "syntax error on line " << line_no << ":\n" << line << "\n\n";
					invalid++;
				}
			}
			catch (...) {
				invalid++;
				cerr << "syntax error\n";
			}
		}
	}
	cout << "\n" << valid << " valid entries\n" << invalid << " invalid entries\n";
	cout << "----------------------------------------\n";
}

//entry point 
//------------------------------------------------------------------------------
bool DBParser::program() {
	if (query()) {
		return true;
	}
	else if (command()) {
		return true;
	}
	else {
		return false;
	}
}

//query ::= relation_name <- expr ;
bool DBParser::query() {
	string name = relation_name();
	if (name.size() > 0) {
		Token assignment_token = ts->get();
		if (assignment_token.get_type() == _assign) {
			if (expr()) {
				return true;
			}
		}
		else {
			ts->unget(assignment_token);
		}
	}

	return false;
}

//command ::= (open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd);
bool DBParser::command() {
	bool value;

		 if (open_cmd())	value = true; 
	else if (close_cmd())	value = true; 
	else if (write_cmd())	value = true; 
	else if (exit_cmd())	value = true; 
	else if (show_cmd())	value = true; 
	else if (create_cmd())	value = true; 
	else if (update_cmd())	value = true; 
	else if (insert_cmd())	value = true; 
	else if (delete_cmd())	value = true; 
	else					value = false;
	
	if (value) {
		Token semicolon_token = ts->get();
		if (semicolon_token.get_type() == _semicolon) {
			return true;
		}
		else {
			ts->unget(semicolon_token);
			return false;
		}
	}
	else {
		return false;
	}
}

//queries
//------------------------------------------------------------------------------

//selection ::= select (condition) atomic_expr
bool DBParser::selection() {
	Token select_token = ts->get();
	if (select_token.get_type() == _select) {
		if (ts->get().get_type() == _lpar) {
			if (condition()) {
				if (ts->get().get_type() == _rpar) {
					if (atomic_expr())
					{

						return true;
					}
				}
			}
		}
	}
	else {
		ts->unget(select_token);
	}

	return false;
}

//projection ::= project (attribute_list) atomic_expr
bool DBParser::projection() {
	Token project_token = ts->get();
	if (project_token.get_type() == _project) {
		if (ts->get().get_type() == _lpar) {
			if (attribute_list()) {
				if (ts->get().get_type() == _rpar) {
					if (atomic_expr()){
						return true;
					}
				}
			}			
		}
	}
	else {
		ts->unget(project_token);
	}

	return false;
}

//renaming ::= rename (attribute_list) atomic_expr
bool DBParser::rename() {
	Token rename_token = ts->get();
	if (rename_token.get_type() == _rename) {
		if (ts->get().get_type() == _lpar) {
			if (attribute_list()) {
				if (ts->get().get_type() == _rpar) {
					if (atomic_expr()) {
						return true;
					}
				}
			}			
		}
	}
	else {
		ts->unget(rename_token);
	}

	return false;
}

//condition ::= conjunction {|| conjunction}
bool DBParser::condition() {
	if (conjunction()) {
		while (true) {
			Token or_token = ts->get();
			if (or_token.get_type() == _or) {
				if (conjunction()) continue;
				else {
					ts->unget(or_token);
					return false;
				}
			}
			else {
				ts->unget(or_token);
				return true;
			}
		}
	}
	
	return false;
}

//conjunction ::= comparison {&& comparison}
bool DBParser::conjunction() {
	if (comparison()) {
		while (true) {
			Token and_token = ts->get();
			if (and_token.get_type() == _and) {
				if (comparison()) continue;
				else {
					ts->unget(and_token);
					return false;
				}
			}
			else {
				ts->unget(and_token);
				return true;
			}
		}
	}
	
	return false;
}

//comparison ::= operand op operand | (condition)
bool DBParser::comparison() {
	if (operand()) {
		if (op()) {
			if (operand()) {
				return true;
			}
		}
	}
	else {
		Token lpar_token = ts->get();
		if (lpar_token.get_type() == _lpar) {
			if (condition()) {
				Token rpar_token = ts->get();
				if (rpar_token.get_type() == _rpar) {
					return true;
				}	
			}
		}
		else {
			ts->unget(lpar_token);
		}
	}

	return false;
}

//op ::= == | != | < | > | <= | >=
bool DBParser::op() {
	Token op_token = ts->get();
	switch (op_token.get_type()) {
	case _equals:
		return true;
	case _not_eq:
		return true;
	case _less:
		return true;
	case _greater:
		return true;
	case _less_eq:
		return true;
	case _greater_eq:
		return true;
	default:
		ts->unget(op_token);
		return false;
	}
}

//operand ::= attribute_name | literal
bool DBParser::operand() {
	if (attribute_name())
		return true;
	else if (literal()) 
		return true;
	else return false;
}


//commands
//------------------------------------------------------------------------------

//open_cmd ::== OPEN relation_name 
bool DBParser::open_cmd() {
	Token open_token = ts->get();
	if (open_token.get_type() == _open) {
		string table_name = relation_name();
		if (table_name.size() > 0) {
			db.Open(table_name);
			return true;
		}
	}
	else {
		ts->unget(open_token);
	}

	return false;
}

//close_cmd ::== CLOSE relation_name 
bool DBParser::close_cmd() {
	Token close_token = ts->get();
	if (close_token.get_type() == _close) {
		string table_name = relation_name();
		if (table_name.size() > 0) {
			db.Close(table_name);
			return true;
		}
	}
	else {
		ts->unget(close_token);
	}

	return false;
}

//write_cmd ::== WRITE relation_name 
bool DBParser::write_cmd() {
	Token write_token = ts->get();
	if (write_token.get_type() == _write) {
		string table_name = relation_name();
		if (table_name.size() > 0) {
			db.Write(table_name);
			return true;
		}
	}
	else {
		ts->unget(write_token);
	}

	return false;
}

//exit_cmd ::== EXIT 
bool DBParser::exit_cmd() {
	Token exit_token = ts->get();
	if (exit_token.get_type() == _exit_program) {
		db.Exit();
		return true;
	}
	else {
		ts->unget(exit_token);
	}

	return false;
}

//show-cmd ::== SHOW atomic_expr 
bool DBParser::show_cmd() {
	Token show_token = ts->get();
	if (show_token.get_type() == _show) {
		if (atomic_expr()) {
			return true;
		}
	}
	else {
		ts->unget(show_token);
	}

	return false;
}

//create-cmd ::= CREATE TABLE relation_name (typed_attribute_list) PRIMARY KEY (attribute_list)
bool DBParser::create_cmd() {
	Token create_token = ts->get();
	if (create_token.get_type() == _create) {
		if (ts->get().get_type() == _table) {
			string table_name = relation_name();
			if (table_name.size() > 0) {

				if (ts->get().get_type() == _lpar) {
					vector<vector<string> > typed_attrs = typed_attribute_list();
					if (typed_attrs.size == 2) {
						if (ts->get().get_type() == _rpar) {

							if (ts->get().get_type() == _primary) {
								if (ts->get().get_type() == _key) {

									if (ts->get().get_type() == _lpar) {
										vector<string> attrs = attribute_list();
										if (attrs.size() > 0) {
											if (ts->get().get_type() == _rpar) {
												
												db.Create(table_name,
													typed_attrs[0],
													typed_attrs[1],
													attrs);
												
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else {
		ts->unget(create_token);
	}

	return false;
}

//update_cmd ::= UPDATE relation_name SET attribute_name = literal { , attribute_name = literal } WHERE condition 
bool DBParser::update_cmd() {
	Token update_token = ts->get();
	if (update_token.get_type() == _update) {
		if (relation_name()) {

			if (ts->get().get_type() == _set) {

				if (attribute_name()) {
					if (ts->get().get_type() == _assign_eq) {

						if (literal()) {
							while (true) {
								Token comma_token = ts->get();
								if (comma_token.get_type() == _comma) {
									if (literal()) continue;
									else {
										ts->unget(comma_token);
										break;
									}
								}
								else {
									ts->unget(comma_token);
									
									if (ts->get().get_type() == _where) {
										if (condition()) {
											return true;
										}
										else break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else {
		ts->unget(update_token);
	}

	return false;
}

//insert_cmd :: = INSERT INTO relation_name VALUES FROM(literal {, literal }) | INSERT INTO relation_name VALUES FROM RELATION expr
bool DBParser::insert_cmd() {
	Token insert_token = ts->get();
	if (insert_token.get_type() == _insert) {
		if (ts->get().get_type() == _into) {
			if (relation_name()) {
				if (ts->get().get_type() == _values) {
					if (ts->get().get_type() == _from) {
																		
						//VALUES FROM(literal {, literal })
						Token lpar_token = ts->get();
						if (lpar_token.get_type() == _lpar) {

							if (literal()) {
								while (true) {
									Token comma_token = ts->get();
									if (comma_token.get_type() == _comma) {
										if (literal()) continue;
										else {
											ts->unget(comma_token);
											break;
										}
									}
									else {
										ts->unget(comma_token);
										
										if (ts->get().get_type() == _rpar) {
											return true;
										}
									}
								}
							}
						}

						//VALUES FROM RELATION expr
						else if (lpar_token.get_type() == _relation) {
							if (expr()) {
								return true;
							}							
						}

					}
				}
			}
		}

	}
	else {
		ts->unget(insert_token);
	}

	return false;
}

//delete_cmd ::= DELETE FROM relation_name WHERE condition
bool DBParser::delete_cmd() {
	Token delete_token = ts->get();
	if (delete_token.get_type() == _delete) {
		if (ts->get().get_type() == _from) {
			string table_name = relation_name();
			if (table_name.size() > 0) {
				if (ts->get().get_type() == _where) {
					vector<int> rows = condition();
					if (rows.size() > 0) {

						//db.Delete(table_name, )

						return true;
					}
				}
			}
		}
	}
	else {
		ts->unget(delete_token);
	}

	return false;
}

//Data structures
//------------------------------------------------------------------------------

//relation_name ::= identifier
string DBParser::relation_name() {
	Token relation_name_token = ts->get();
	if (relation_name_token.get_type() == _identifier) {
		return relation_name_token.get_name;
	}
	else {
		ts->unget(relation_name_token);
		return "";
	}
}

//union ::= atomic_expr + atomic_expr
//difference ::= atomic_expr - atomic_expr
//product ::= atomic_expr * atomic_expr 
//expr ::= atomic-expr | selection | projection | renaming | union | difference | product
bool DBParser::expr() {
	if (selection())
		return true;
	else if (projection())
		return true;
	else if (rename())
		return true;
	else if (atomic_expr()) {
		Token expr_token = ts->get();
		if (expr_token.get_type() == _plus) {
			if (atomic_expr()) {
				return true;
			}
			else return false;
		}
		else if (expr_token.get_type() == _minus) {
			if (atomic_expr()) {
				return true;
			}
			else return false;
		}
		else if (expr_token.get_type() == _multiply) {
			if (atomic_expr()) {
				return true;
			}
			else return false;
		}
		else {
			ts->unget(expr_token);
			return true;
		}
	}
	else {
		return false;
	}
}

//atomic_expr ::= relation_name | (expr)
bool DBParser::atomic_expr() {
	Token lpar_token = ts->get();
	if (lpar_token.get_type() == _lpar) {
		if (expr()) { 
			Token rpar_token = ts->get();
			if (rpar_token.get_type() == _rpar) {
				return true;
			}
		}
		return false;
	}
	else {
		ts->unget(lpar_token);
		string table_name = relation_name();
		if (table_name.size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}
}

//attribute_name ::= identifier
string DBParser::attribute_name() {
	Token identifier_token = ts->get();
	if (identifier_token.get_type() == _identifier) {
		return identifier_token.get_name();
	}
	else {
		ts->unget(identifier_token);
		return false;
	}
}

//type ::= VARCHAR(integer) | INTEGER
string DBParser::type() {
	Token type_token = ts->get();
	stringstream ss;
	switch(type_token.get_type()) {
	case _int_type:
		ss << "INTEGER";
		return ss.str();
	case _varchar:
		ss << "VARCHAR(" << (int)type_token.get_value() << ")";
		return ss.str();
	default:
		ts->unget(type_token);
		return "";
	}
}

//typed_attribute_list ::= attribute_name type {, attribute_name type}
vector<vector<string> > DBParser::typed_attribute_list() { //need to return vector<typed_attribute>
	vector<vector<string> > typed_attrs;
	typed_attrs.push_back(vector<string>()); //attr_name
	typed_attrs.push_back(vector<string>()); //type

	string attr_name = attribute_name();
	if (attr_name.size() > 0) {
		string type = type();
		if (type.size() > 0) {
			typed_attrs[0].push_back(attr_name);
			typed_attrs[1].push_back(type);

			while (true) {
				Token comma_token = ts->get();
				if (comma_token.get_type() == _comma) {
					attr_name = attribute_name();
					if (attr_name.size() > 0) {
						type = type();
						if (type.size() > 0) {
							typed_attrs[0].push_back(attr_name);
							typed_attrs[1].push_back(type);
						}
						else {
							typed_attrs.clear();
							return typed_attrs;
						}
					}
					else {
						ts->unget(comma_token);
						return typed_attrs;
					}
				}
			}
		}

		typed_attrs.clear();
		return typed_attrs;
	}
}

//attribute_list ::= attribute_name {, attribute_name} 
vector<string> DBParser::attribute_list() {
	vector<string> attr_list;
	string attr_name = attribute_name();
	if (attr_name.size() > 0) {
		attr_list.push_back(attr_name);

		while (true) {
			Token comma_token = ts->get();
			if (comma_token.get_type() == _comma) {
				string attr_name = attribute_name();
				if (attr_name.size() > 0) {
					attr_list.push_back(attr_name);
					continue;
				}
				else {
					ts->unget(comma_token);
					attr_list.clear();
					return attr_list;
				}
			}
			else {
				ts->unget(comma_token);
				return attr_list;
			}
		}
	}
	
	attr_list.clear();
	return attr_list;
}

//literal ::= "identifier" | integer | float
Token DBParser::literal() {
	Token literal_token = ts->get();
	if (literal_token.get_type() == _quotation) {
		Token string_token = ts->get();
		if (string_token.get_type() == _identifier) {
			Token end_quote_token = ts->get();
			if (end_quote_token.get_type() == _quotation) {
				return string_token;
			}
		}
	}
	else if (literal_token.get_type() == _int_num) {
		return literal_token;
	}
	else if (literal_token.get_type() == _float_num) {
		return literal_token;
	}
	else {
		ts->unget(literal_token);
		return Token(_null);
	}
}