

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Database.h"
using namespace std;
int main(){
	Database db = Database();
	db.Create("People", vector<string>{ "name", "age", "occupation" }, vector<string>{ "VARCHAR(10)", "INTEGER", "VARCHAR(64)" }, vector<string>{"name"});
	db.Insert("People", vector < string > {"alan", "21", "broke cs student"});
	db.Insert("People", vector < string > {"jacob", "21", "Napa flats"});
	db.Insert("People", vector < string > {"robby", "21", "Hockey baller"});
	db.Insert("People", vector < string > {"casey", "21", "notbroke cs student"});//testing insert

	db.Show("People");//testing insert and show
	db.Write("People");//testing write
	db.Close("People");
	db.Show("People");//testing close
	
	db.Open("People");
	db.Insert("People", vector < string > {"new entry", "18", "professional fish"});
	db.Show("People"); //testing open

	db.Update("People", vector < string > {"name", "occupation"}, vector < string > {"John", "plumber"}, "name", Token_Type::_equals, "new entry");
	db.Show("People");//Testing update
	
	db.Create("cs_students", vector<string>{ "name", "age", "occupation" }, vector<string>{ "VARCHAR(10)", "INTEGER", "VARCHAR(64)" }, vector<string>{"name"});
	db.Insert("cs_students", db.Select("selection", "People", "age", Token_Type::_equals, "21"));//Inserts all tuples where age is 21
	db.Show("cs_students");//testing Insert of relation and selection of multiple values

	db.Delete("cs_students", "name", Token_Type::_not_eq, "blank");//deletes all entries where name!="blank"
	db.Show("cs_students");//testing delete

	db.Insert("cs_students",db.Select("selection","People","name",Token_Type::_equals,"alan"));
	db.Insert("cs_students", db.Select("selection", "People", "name", Token_Type::_equals, "casey"));
	db.Show("cs_students");//testing insert of selection of single value

	db.Show(db.Set_union("all", "cs_students", "People")); //Testing union
	db.Show(db.Set_difference("some", "cs_students", "People"));// Testing difference cs_students - people, should be empty
	db.Show(db.Set_difference("some", "People", "cs_students"));//Testing difference people - cs_students, should be smaller

	db.Rename("first_name", "name", "People");//updates attribute "name" to "first_name"
	db.Show("People");//Testing Rename

	db.Show(db.Project("People_projection", "People", vector < string > {"first_name", "occupation"}));//Testing Projection


	db.Create("Pets", vector<string>{ "name", "breed"}, vector<string>{ "VARCHAR(20)", "VARCHAR(20)" }, vector<string>{"name"});
	db.Insert("Pets", vector < string > {"derpy", "dog"});
	db.Insert("Pets", vector < string > {"chirpy", "bird"});
	db.Show("Pets");

	db.Show(db.Cross_product("People*Pets", "People", "Pets"));//Testing Cross Product
	string block;
	cout << "input anything to continue with database exit\n";
	cin >> block;
	db.Exit();//Testing exit
	cout << "HEY DATABASE DIDNT EXIT\n";
	cin >> block;
	return 0;
}