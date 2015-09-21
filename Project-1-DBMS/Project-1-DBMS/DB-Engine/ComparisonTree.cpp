#include "ComparisonTree.h"
#include <iostream>

	Comparison_tree::Comparison_tree(){
		this.root = NULL;
		this.data_table = Table();
	}
	Comparison_tree::Comparison_tree(Node *root, Table table){
		this.root = root;
		this.data_table = table;
	}
	//constructor that makes a new tree from 2 existing trees
	Comparison_tree::Comparison_tree(string new_root_value, Token_Type new_root_type, Comparison_tree *left_tree, Comparison_tree *right_tree){
		this.root = new Node(new_root_value, new_root_type, left_tree->Get_root(), right_tree->Get_root());
		this.data_table = Table();
	}
	
	ComparisonTree::~Comparison_tree() { 
		if (this.root != NULL) 
			delete this.root; 
	}

	Node* Comparison_tree::Get_root(){
		return this.root;
	}
	void Comparison_tree::Set_root(Node *n){
		this.root = n;
	}

	//sets table and calls eval node on root
	vector<int> Comparison_tree::Eval_tree(const Table& table){
		this.data_table = table;
		return Eval_node(this.root);
	}

	vector<int> Comparison_tree::Eval_node(Node* n){
		vector<int> valid_rows, left_rows, right_rows;
		switch(n->Type){
		case _varchar: //expected type at the root of comparison tree is an operator, comparison(<,==,>,...) or && or ||
		case _int_num:
			cerr << "Can not evaluate a comparison with a literal as the root, literal must be lhs or rhs\n";
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
					valid_rows.push_back(right_rows[i]); //when a match is not found push it back, we do not want duplicates
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
				for (unsigned int i = 0; i < this.data_table.Get_max_height(); ++i)
					if (this.data_table[left->value].Get_name() != "DefaultName") //perform check because if attribute does not exist it will return a defualt table
						if (this.data_table[left->value][i] < right->value) //dont want to try to access data from a default table
							valid_rows.push_back(i); //store row index if comparison evaluates to true
				return valid_rows;
				break;
			case(Token_Type::_less_eq) : //rinse and repeat
				for (unsigned int j = 0; j< this.data_table.Get_max_height(); ++j) //used different letter for debugging purposes
					if (this.data_table[left->value].Get_name() != "DefaultName")
						if (this.data_table[left->value][j] <= right->value)//[] operator for table returns attribute(column) of table. [] operator of attribute returns value
							valid_rows.push_back(j);
				return valid_rows;
				break;
			case(Token_Type::_greater) :
				for (unsigned int k = 0; k< this.data_table.Get_max_height(); ++k)
					if (this.data_table[left->value].Get_name() != "DefaultName")
						if (this.data_table[left->value][k] > right->value)
							valid_rows.push_back(k);
				return valid_rows;
				break;
			case(Token_Type::_greater_eq) :
				for ( unsigned int l = 0; l < this.data_table.Get_max_height(); ++l)
					if (this.data_table[left->value].Get_name() != "DefaultName")
						if (this.data_table[left->value][l] >= right->value)
							valid_rows.push_back(l);
				return valid_rows;
				break;
			case(Token_Type::_equals) :
				for ( unsigned int m = 0; m < this.data_table.Get_max_height(); ++m)
					if (this.data_table[left->value].Get_name()!="DefaultName")
						if (this.data_table[left->value][m]== right->value)
							valid_rows.push_back(m);
				return valid_rows;
				break;
			case(Token_Type::_not_eq) :
				for ( unsigned int n = 0; n < this.data_table.Get_max_height(); ++n)
					if (this.data_table[left->value].Get_name() != "DefaultName")
						if (this.data_table[left->value][n] != right->value)
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