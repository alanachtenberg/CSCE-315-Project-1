#include "Table.h"
#include "Node.h";

class Comparison_tree
{

private:
	Node Root;
public:

	Comparison_tree();
	
	Node Get_root();
	void Set_root(Node n);

	//returns vector of ints corresponding to rows that evaluate to true;
	vector<int> Eval_node(Node n, const Table& t);
	
	//calls eval_node on root
	vector<int> Eval_tree(const Table& t);

	

};