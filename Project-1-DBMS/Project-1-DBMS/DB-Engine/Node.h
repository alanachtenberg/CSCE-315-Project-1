#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

enum Token_Type {
	_lpar, _rpar, _plus, _minus, _multiply, _divide, _mod, _assign, _semicolon,
	_quotation, _comma, _assign_eq,
	_equals, _not_eq, _less, _less_eq, _greater, _greater_eq,
	_and, _or,
	_create, _insert, _select, _project, _show, _rename,
	_into, _table, _values, _from, _primary, _key,
	_relation, _write, _open, _close, _delete, _update, _set, _where,
	_int_type, _int_num, _float_type, _float_num, _varchar, _char, _identifier,
	_exit_program, _null
};

class Node{

private:
	Node* Left;
	Node* Right;
public:
	Token_Type Type;
	string Value;

	Node();
	Node(string value, Token_Type type, Node *left=NULL, Node *right=NULL);
	Node(const Node& node);

	//Getters
	Node& Get_left();
	Node& Get_right();
	//Setters
	void Set_left(Node n);
	void Set_right(Node n);
	
	//check if node is int or string
	bool Is_literal() const;

	ostream& Print_node(ostream& os);
};

#endif