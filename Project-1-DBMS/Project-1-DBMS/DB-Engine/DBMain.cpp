/*#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Database.h"
using namespace std;
int main(){
	//CREATE COMPARSION TREE
	Node* left = new Node("name",_varchar);
	Node* right = new Node("alan", _varchar);
	Node* right2 = new Node("jacob", _varchar);
	Node* comp1 = new Node(">", _greater, left, right2);
	Node* comp2 = new Node("==", _equals, left, right);
	Node* root = new Node("&&", _and, comp1, comp2);
	Comparison_tree tree;
	tree.Set_root(*root);

	

	Database db = Database();
	Table table = db.Create("People", vector<string>{ "name", "age", "occupation" }, vector<string>{ "VARCHAR(10)", "INTEGER", "VARCHAR(64)" }, vector<string>{"name"});
	db.Insert(table, vector < string > {"alan", "21", "broke cs student"});
	db.Insert(table, vector < string > {"jacob", "21", "Napa flats"});
	db.Insert(table, vector < string > {"robby", "21", "Hockey baller"});
	db.Insert(table, vector < string > {"casey", "21", "notbroke cs student"});//testing insert
	//TEST COMPARISON TREE
	vector<int> temp=tree.Eval_tree(db.Get_table("People"));

	db.Show("People");//testing insert and show
	//db.Write("People");//testing write
	//db.Close("People");
	//db.Show("People");//testing close
	
	//db.Open("People");
	//db.Insert("People", vector < string > {"new entry", "18", "professional fish"});
	//db.Show("People"); //testing open

	//db.Update("People", vector < string > {"name", "occupation"}, vector < string > {"John", "plumber"}, "name", Token_Type::_equals, "new entry");
	//db.Show("People");//Testing update
	
	//db.Create("cs_students", vector<string>{ "name", "age", "occupation" }, vector<string>{ "VARCHAR(10)", "INTEGER", "VARCHAR(64)" }, vector<string>{"name"});
	//db.Insert("cs_students", db.Select("selection", "People", tree));//Inserts all tuples where age is 21
	//db.Show("cs_students");//testing Insert of relation and selection of multiple values

	//db.Delete("cs_students", "name", Token_Type::_not_eq, "blank");//deletes all entries where name!="blank"
	//db.Show("cs_students");//testing delete

	//db.Insert("cs_students",db.Select("selection","People",tree));
	//db.Show("cs_students");//testing insert of selection of single value

	//db.Show(db.Set_union("all", "cs_students", "People")); //Testing union
	//db.Show(db.Set_difference("some", "cs_students", "People"));// Testing difference cs_students - people, should be empty
	//db.Show(db.Set_difference("some", "People", "cs_students"));//Testing difference people - cs_students, should be smaller

	//db.Rename("first_name", "name", "People");//updates attribute "name" to "first_name"
	//db.Show("People");//Testing Rename

	//db.Show(db.Project("People_projection", "People", vector < string > {"first_name", "occupation"}));//Testing Projection


	//db.Create("Pets", vector<string>{ "name", "breed"}, vector<string>{ "VARCHAR(20)", "VARCHAR(20)" }, vector<string>{"name"});
	//db.Insert("Pets", vector < string > {"derpy", "dog"});
	//db.Insert("Pets", vector < string > {"chirpy", "bird"});
	//db.Show("Pets");

	//db.Show(db.Cross_product("People*Pets", "People", "Pets"));//Testing Cross Product
	string block;
	cout << "input anything to continue with database exit\n";
	
	cin >> block;
	db.Exit();//Testing exit
	cout << "HEY DATABASE DIDNT EXIT\n";
	cin >> block;
	return 0;
}*/