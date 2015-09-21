#ifndef NODE_H
#define NODE_H

//#include <std::string>
#include "Token.h"
using namespace std;

class Node{

private:
	Node* left;
	Node* right;
public:
	Token_Type type; //type of value, can be operator(less or greater equals etc) or literal (number varchar)
	std::string value;

	Node();
	Node(std::string value, Token_Type type, Node *left=NULL, Node *right=NULL);
	Node(const Node& node);
	~Node();
	//Getters
	Node* Get_left();
	Node* Get_right();
	//Setters
	void Set_left(Node n);
	void Set_right(Node n);
	
	//check if node is int or std::string
	bool Is_literal() const;

	ostream& Print_node(ostream& os);
};

#endif