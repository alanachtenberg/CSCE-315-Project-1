#ifndef NODE_H
#define NODE_H

//#include <std::string>
#include "Token.h"
using namespace std;

class Node{

private:
	Node* Left;
	Node* Right;
public:
	Token_Type Type;
	std::string Value;

	Node();
	Node(std::string value, Token_Type type, Node *left=NULL, Node *right=NULL);
	Node(const Node& node);
	~Node();
	//Getters
	Node& Get_left();
	Node& Get_right();
	//Setters
	void Set_left(Node n);
	void Set_right(Node n);
	
	//check if node is int or std::string
	bool Is_literal() const;

	ostream& Print_node(ostream& os);
};

#endif