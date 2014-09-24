


#include "ComparisonTree.h";


	Comparison_tree::Comparison_tree(){
		Root = Node();
		Data_table = Table();
	}

	Node Comparison_tree::Get_root(){
		return Root;
	}
	void Comparison_tree::Set_root(Node n){
		Root = n;
	}

	//sets table and calls eval node on root
	vector<int> Comparison_tree::Eval_tree(const Table& table){
		Data_table = table;
		return Eval_node(Root);
	}

	vector<int> Comparison_tree::Eval_node(Node n){
		vector<int> valid_rows;
		switch(n.Type){
		case (Token_Type::_varchar, Token_Type::_int_num) :
			cerr << "Can not evaluate a comparison with a literal as the root, literal must be lhs or rhs" << endl;
			break;
		case (_less,_less_eq) :
			return Compare(n.Get_left(), n.Type, n.Get_right());
			break;
		default:
			cerr << "error unknown token type\n";
			
		}
	}

	vector<int>	Comparison_tree::Compare(const Node& left,const Token_Type& type,const Node& right ){
		vector<int> valid_rows;
		if (left.Is_literal() && right.Is_literal()){
			switch (type){
			case(Token_Type::_less):
				for (int i = 0; i < Data_table.Get_max_height(); ++i)
					if (Data_table[left.Value][i] < right.Value)
						valid_rows.push_back(i);
				return valid_rows;
			case(Token_Type::_less_eq) :
				for (int i = 0; i < Data_table.Get_max_height(); ++i)
					if (Data_table[left.Value][i] <= right.Value)
						valid_rows.push_back(i);
				return valid_rows;
			case(Token_Type::_greater) :
				for (int i = 0; i < Data_table.Get_max_height(); ++i)
					if (Data_table[left.Value][i] > right.Value)
						valid_rows.push_back(i);
				return valid_rows;
			case(Token_Type::_greater_eq) :
				for (int i = 0; i < Data_table.Get_max_height(); ++i)
					if (Data_table[left.Value][i] >= right.Value)
						valid_rows.push_back(i);
				return valid_rows;
			case(Token_Type::_equals) :
				for (int i = 0; i < Data_table.Get_max_height(); ++i)
					if (Data_table[left.Value][i] == right.Value)
						valid_rows.push_back(i);
				return valid_rows;
			case(Token_Type::_not_eq) :
				for (int i = 0; i < Data_table.Get_max_height(); ++i)
					if (Data_table[left.Value][i] != right.Value)
						valid_rows.push_back(i);
				return valid_rows;
			default:
				cerr << "error not a simple comparison, < , <= , > , >= , == , !=\n";
			}
		}
		else
			cerr << "error  < expected literal on both sides\n";
		return vector<int>();
	}