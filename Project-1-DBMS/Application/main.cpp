#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
//#include "Database\DBParser.h"
#include "main_menu.h"

using namespace std;


//Global  DBparser, interfaces queries to internal database
DBParser dbparser;

void Initialize_db(){
	cout << "Initializing Database\n\n";

	if (dbparser.execute_query("OPEN addressbook;").Get_name() == "Default"){ // if open not successful, create addressbook
		dbparser.execute_query("CREATE TABLE addressbook (name VARCHAR(30), phone VARCHAR(10), email VARCHAR(50), address VARCHAR(100)) PRIMARY KEY (name);");
		cout << "addressbook.db created\n";
	}
	else
		cout << "addressbook.db opened\n";

	if (dbparser.execute_query("OPEN calendar;").Get_name() == "Default"){ // if open not successful, create calendar
		dbparser.execute_query("CREATE TABLE calendar (date VARCHAR(8)) PRIMARY KEY (date);");
		cout << "calendar.db created\n";
	}
	else
		cout << "calendar.db opened\n";

	if (dbparser.execute_query("OPEN memopad;").Get_name() == "Default"){ // if open not successful, create memopad
		dbparser.execute_query("CREATE TABLE memopad (memo VARCHAR(1000), date VARCHAR(8), name VARCHAR(30)) PRIMARY KEY (memo);");
		cout << "memopad.db created\n";
	}
	else
		cout << "memopad.db opened\n";

	if (dbparser.execute_query("OPEN todolist;").Get_name() == "Default"){ // if open not successful, create todolist
		dbparser.execute_query("CREATE TABLE todolist (todo VARCHAR(1000), date VARCHAR(8)) PRIMARY KEY (todo);");
		cout << "todolist.db created\n\n";
	}
	else
		cout << "todolist.db opened\n\n";

	cout << "Database Initialized\n\n";
}

void Close_db(){
	cout << "Saving to Database\n";

	dbparser.execute_query("WRITE addressbook;");
	dbparser.execute_query("WRITE calendar;");
	dbparser.execute_query("WRITE memopad;");
	dbparser.execute_query("WRITE todolist;");

	dbparser.execute_query("CLOSE addressbook;");
	dbparser.execute_query("CLOSE calendar;");
	dbparser.execute_query("CLOSE memopad;");
	dbparser.execute_query("CLOSE todolist;");
	dbparser.execute_query("EXIT;");
}

int main(){
	Initialize_db();
	main_menu(dbparser);
	Close_db();
	return 0;
}