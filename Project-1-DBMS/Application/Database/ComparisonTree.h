#ifndef COMPARISON_TREE_H
#define COMPARISON_TREE_H

#include "Table.h"
#include "Node.h"

class Comparison_tree
{

private:
	Node * Root;
	Table Data_table; //data table is the table that all the comparisons will be performed on
	//returns vector of ints corresponding to rows that evaluate to true;
	std::vector<int> Eval_node(Node* n); //evalutates individual nodes
	std::vector<int> Compare(Node* left, const Token_Type& type, Node* right); //compares literals

public:

	Comparison_tree();
	//constructs a tree, by setting Root node
	Comparison_tree(Node *root, Table table=Table());
	//constructor that makes a new tree from 2 existing trees
	Comparison_tree(std::string new_root_value, Token_Type new_root_type, Comparison_tree *left_tree, Comparison_tree *right_tree);
	~Comparison_tree() { if (Root != NULL) delete Root; }
	Node* Get_root();
	void Set_root(Node *n);


	//calls eval_node on root
	std::vector<int> Eval_tree(const Table& table);

};

#endif