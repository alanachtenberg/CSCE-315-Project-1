#include "Node.h"
#include <stdio.h>
#include <iostream>

	Node::Node(){
		Left = NULL;
		Right = NULL;
		Type = Token_Type::_null;
		Value = "";
	}
	Node::Node(string value, Token_Type type, Node* left, Node* right){
		Value = value;
		Type = type;
		Left = left;
		Right = right;
	}

	Node::Node(const Node& node){
		Left = node.Left;//copy of a pointer not object it points to
		Right = node.Right;
		Type = node.Type;
		Value = node.Value;
	}

	//Get
	Node& Node::Get_left(){
		if (Left == NULL)
			cerr << "cant Get, left pointer null" << endl;
		return *Left;
	}

	Node& Node::Get_right(){
		if (Right == NULL)
			cerr << "cant Get, right pointer null" << endl;
		return *Right;
	}

	void Node::Set_left(Node n){
		Left = new Node(n);
	}
	void Node::Set_right(Node n){
		Right = new Node(n);
	}
	bool Node::Is_literal() const {
		return (Type == _int_num || Type == _varchar);
	}
	ostream& Node::Print_node(ostream& os){
		os <<"value: " <<Value << " type: " << Type<<endl;
		return os;
	}