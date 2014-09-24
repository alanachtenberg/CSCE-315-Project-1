


#include "ComparisonTree.h";


	Comparison_tree::Comparison_tree(){
		Root = Node();
	}

	Node Comparison_tree::Get_root(){
		return Root;
	}
	void Comparison_tree::Set_root(Node n){
		Root = n;
	}