#include "ComparisonTree.h"
#include <iostream>

	Comparison_tree::Comparison_tree(){
		Root = NULL;
		Data_table = Table();
	}
	Comparison_tree::Comparison_tree(Node *root, Table table){
		Root = root;
		Data_table = table;//table is default parameter
	}
	//constructor that makes a new tree from 2 existing trees
	Comparison_tree::Comparison_tree(string new_root_value, Token_Type new_root_type, Comparison_tree *left_tree, Comparison_tree *right_tree){
		Root = new Node(new_root_value, new_root_type, left_tree->Get_root(), right_tree->Get_root());
		Data_table = Table();
	}


	Node* Comparison_tree::Get_root(){
		return Root;
	}
	void Comparison_tree::Set_root(Node *n){
		Root = n;
	}

	//sets table and calls eval node on root
	vector<int> Comparison_tree::Eval_tree(const Table& table){
		Data_table = table;
		return Eval_node(Root);
	}

	vector<int> Comparison_tree::Eval_node(Node* n){
		vector<int> valid_rows, left_rows, right_rows;
		switch(n->Type){
		case _varchar://expected type in the middle is an operator or && or |||
		case _int_num:
			cerr << "Can not evaluate a comparison with a literal as the root, literal must be lhs or rhs" << endl;
			break;
		case _less:
		case _less_eq:
		case _greater:
		case _greater_eq:
		case _equals:
		case _not_eq ://simple comparison cases
			return Compare(n->Get_left(), n->Type, n->Get_right());
			break;
		case _and ://and case
			left_rows = Eval_node(n->Get_left());//evaluate left
			right_rows = Eval_node(n->Get_right());//evaluate right
			for ( unsigned int i = 0; i < left_rows.size(); ++i)
				for ( unsigned int j = 0; j < right_rows.size(); ++j)
					if (left_rows[i] == right_rows[j]) // check if left row number matches any in right
						valid_rows.push_back(left_rows[i]);
			return valid_rows;
			break;
		case _or : //or case
			left_rows = Eval_node(n->Get_left());//evaluate left
			right_rows = Eval_node(n->Get_right());//evaluate right

			valid_rows = left_rows;//get all left side
			for ( unsigned int i = 0; i < right_rows.size(); ++i){
				bool found = false;
				for ( unsigned int j = 0; j < left_rows.size(); ++j) //search for a match of rightrow in all left rows
					if (right_rows[i] == left_rows[j])
						found = true;
				if (!found)
					valid_rows.push_back(right_rows[i]); //when a match is not found push it back, we do this because we do not want duplicates
			}
			return valid_rows;
			break;
		default:
			cerr << "error unknown token type\n";
		}
		return valid_rows;
	}

	vector<int>	Comparison_tree::Compare(Node* left,const Token_Type& type, Node* right ){
		vector<int> valid_rows;
		if (left->Is_literal() && right->Is_literal()){//check to make sure we have the correct left and right argument types
			switch (type){
			case(Token_Type::_less):
				for (unsigned int i = 0; i < Data_table.Get_max_height(); ++i)
					if (Data_table[left->Value].Get_name() != "DefaultName") //perform check because if attribute does not exist it will return a defualt table
						if (Data_table[left->Value][i] < right->Value) //dont want to try to access data from a default table
							valid_rows.push_back(i); //store row index if comparison evaluates to true
				return valid_rows;
				break;
			case(Token_Type::_less_eq) : //rinse and repeat
				for (unsigned int j = 0; j< Data_table.Get_max_height(); ++j) //used different letter for debugging purposes
					if (Data_table[left->Value].Get_name() != "DefaultName")
						if (Data_table[left->Value][j] <= right->Value)
							valid_rows.push_back(j);
				return valid_rows;
				break;
			case(Token_Type::_greater) :
				for (unsigned int k = 0; k< Data_table.Get_max_height(); ++k)
					if (Data_table[left->Value].Get_name() != "DefaultName")
						if (Data_table[left->Value][k] > right->Value)
							valid_rows.push_back(k);
				return valid_rows;
				break;
			case(Token_Type::_greater_eq) :
				for ( unsigned int l = 0; l < Data_table.Get_max_height(); ++l)
					if (Data_table[left->Value].Get_name() != "DefaultName")
						if (Data_table[left->Value][l] >= right->Value)
							valid_rows.push_back(l);
				return valid_rows;
				break;
			case(Token_Type::_equals) :
				for ( unsigned int m = 0; m < Data_table.Get_max_height(); ++m)
					if (Data_table[left->Value].Get_name()!="DefaultName")
						if (Data_table[left->Value][m]==right->Value)
							valid_rows.push_back(m);
				return valid_rows;
				break;
			case(Token_Type::_not_eq) :
				for ( unsigned int n = 0; n < Data_table.Get_max_height(); ++n)
					if (Data_table[left->Value].Get_name() != "DefaultName")
						if (Data_table[left->Value][n] != right->Value)
							valid_rows.push_back(n);
				return valid_rows;
				break;
			default:
				cerr << "error not a simple comparison, < , <= , > , >= , == , !=\n";
			}
		}
		else
			cerr << "error  < expected literal on both sides\n";
		return vector<int>();
	}