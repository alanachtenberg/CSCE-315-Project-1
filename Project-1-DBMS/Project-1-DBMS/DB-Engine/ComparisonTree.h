#ifndef COMPARISON_TREE_H
#define COMPARISON_TREE_H

#include "Table.h"
#include "Node.h"

class Comparison_tree
{

private:
	Node Root;
	Table Data_table;
	//returns vector of ints corresponding to rows that evaluate to true;
	vector<int> Eval_node(Node n);
	vector<int>	Compare(const Node& left, const Token_Type& type, const Node& right);

public:

	Comparison_tree();
	
	Node Get_root();
	void Set_root(Node n);


	//calls eval_node on root
	vector<int> Eval_tree(const Table& table);

};

#endif