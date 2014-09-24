#include "Table.h"
#include "Node.h";

class Comparison_tree
{

private:
	Node Root;
	Table Data_table;
public:

	Comparison_tree();
	
	Node Get_root();
	void Set_root(Node n);

	//returns vector of ints corresponding to rows that evaluate to true;
	vector<int> Eval_node(Node n);
	vector<int>	Compare(const Node& left, const Token_Type& type, const Node& right);

	//calls eval_node on root
	vector<int> Eval_tree(const Table& table);

};