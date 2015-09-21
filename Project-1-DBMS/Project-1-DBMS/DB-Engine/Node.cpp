#include "Node.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

	Node::Node(){
		this.left = NULL;
		this.right = NULL;
		Type = Token_Type::_null;
		Value = "";
	}
	Node::Node(string value, Token_Type type, Node* left, Node* right){
		this.value = value;
		this.type = type;
		this.left = left;//copy of a pointer not object it points to
		this.right = right;
	}

	Node::Node(const Node& node){
		this.left = node.left;//copy of a pointer not object it points to
		this.right = node.right;
		this.type = node.type;
		this.value = node.value;
	}
	Node::~Node(){
		if (this.left != NULL) delete this.left; //delete children
		if (this.right != NULL) delete this.right;
	}

	//Get
	Node* Node::Get_left(){
		if (this.left == NULL)
			cerr << "cant Get, left pointer null" << endl;
		return this.left; // return pointer to left node
	}

	Node* Node::Get_right(){
		if (this.right == NULL)
			cerr << "cant Get, right pointer null" << endl;
		return this.right; // return pointer to right node
	}

	void Node::Set_left(Node n){
		this.left = new Node(n);
	}
	void Node::Set_right(Node n){
		this.right = new Node(n);
	}
	bool Node::Is_literal() const {
		return (this.type == _int_num || this.type == _varchar); //check if node is a number or varchar, else its not a literal
	}
	ostream& Node::Print_node(ostream& os){
		os << "value: " << this.value << " type: " << this.type << endl; // simple print
		return os;
	}