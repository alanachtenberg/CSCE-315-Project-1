#include "Token_Stream.h"
#include <iostream>
#include <iomanip>

using namespace std;

string commands[] = {
	"<- <= < > >= == != && || + - * / %;",
	"CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);",
	"INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);",
	"SHOW animals;",
	"dogs <- select (kind == \"dog\") animals;",
	"cats_or_dogs <- dogs + (select (kind == \"cat\") animals);",
	"INSERT INTO species VALUES FROM RELATION project (kind) animals;",
	"a <- rename (aname, akind) (project (name, kind) animals);",
	"common_names <- project (name) (select (aname == name && akind != kind) (a * animals));",
	"WRITE animals;",
	"CLOSE animals;",
	"EXIT;"
};

int main(){
	try {
		istringstream ss(commands[0]);

		Token_stream ts(ss);

		vector<Token> tokens = ts.tokenize();

		for (int i = 0; i < tokens.size(); i++) {
			Token t = tokens[i];
			cout << " type: "	<< left << setw(15) << t.get_type_name() << 
					" name: "	<< left << setw(15) << t.get_name() << 
					" value: "	<< left << setw(15) << t.get_value() << "\n";
		}
	}
	catch (const exception& e) {
		cerr << "Exception: " << e.what() << "\n";
	}
	catch (...) {
		cerr << "Something went horribly wrong and your are a horrible person\n";
	}

	
	cout << "enter 'exit'";
	string value;
	while (value != "exit") {
		cin >> value;
	}
	return 0;
}