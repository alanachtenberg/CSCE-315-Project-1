

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
	db.Insert("People", vector < string > {"casey", "21", "not broke cs student"});
	db.Show("People");
	db.Write("People");
	return 0;
}