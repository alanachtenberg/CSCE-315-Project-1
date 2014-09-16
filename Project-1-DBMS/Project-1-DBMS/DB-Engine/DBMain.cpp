

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
	db.Insert("People", vector < string > {"casey", "21", "notbroke cs student"});

	db.Show("People");
	db.Write("People");
	db.Close("People");
	db.Show("People");
	db.Open("People");
	db.Insert("People", vector < string > {"new entry", "18", "professional fish"});
	db.Show("People");
	
	db.Create("cs_students", vector<string>{ "name", "age", "occupation" }, vector<string>{ "VARCHAR(10)", "INTEGER", "VARCHAR(64)" }, vector<string>{"name"});
	db.Insert("cs_students", db.Select("selection", "People", "age", Token_Type::_equals, "21"));

	db.Show("cs_students");

	db.Delete("cs_students", "name", Token_Type::_not_eq, "blank");//deletes all entries where name!="blank"
	db.Show("cs_students");

	db.Insert("cs_students",db.Select("selection","People","name",Token_Type::_equals,"alan"));
	db.Insert("cs_students", db.Select("selection", "People", "name", Token_Type::_equals, "casey"));
	db.Show("cs_students");

	db.Show(db.Set_union("all", "cs_students", "People"));
	db.Show(db.Set_difference("some", "cs_students", "People"));
	db.Show(db.Set_difference("some", "People", "cs_students"));

	return 0;
}