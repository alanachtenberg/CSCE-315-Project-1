#include "Token_Stream.h"
#include "DBParser.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int test_case = 2;

vector<string> tests = {
	//"dogs <- select ((aname > name) && (aname == ggg || aname == hhh)) animals;",
	//"CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);",
	//"UPDATE animals SET species = \"lion\" WHERE (age > 4 && (teeth_count != 17));"

	//"CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);",

	//"INSERT INTO animals VALUES FROM(\"Joe\", \"cat\", 4);",
	//"INSERT INTO animals VALUES FROM(\"Spot\", \"dog\", 10);",
	//"INSERT INTO animals VALUES FROM(\"Snoopy\", \"dog\", 3);",
	//"INSERT INTO animals VALUES FROM(\"Tweety\", \"bird\", 1);",
	//"INSERT INTO animals VALUES FROM(\"Joe\", \"bird\", 2);",

	//"SHOW animals;",

	"dogs <-select (kind == \"dog\") animals;",
	//"old_dogs <- select (age > 10) dogs;",

	"cats_or_dogs<-dogs+(select(kind==\"cat\")animals);",

	//"CREATE TABLE species(kind VARCHAR(10)) PRIMARY KEY(kind);",

	//"INSERT INTO species VALUES FROM RELATION project(kind) animals;",

	//"a <- rename(aname, akind) (project(name, kind) animals);",
	//"common_names <- project (name) (select ((aname > name) && (aname == ggg || aname == hhh)) animals) nerds;",
	//"answer <- common_names;",

	//"SHOW answer;",

	//"WRITE animals;",
	//"CLOSE animals;",

	"EXIT;"

};

void test_tokenizer() {
	for (int i = 0; i < tests.size(); i++) {
		try {
			Token_stream ts(tests[i]);

			Token token = ts.get();
			cout << tests[i] << "\n";
			cout << token.get_type_name() << " ";

			while (true) {
				if (token.get_type() == _semicolon) {
					break;
				}
				token = ts.get();
				cout << token.get_type_name() << " ";
				if (token.get_type() == _varchar) {
					cout << token.get_value() << " ";
				}
				cout << "\n";
			}
			cout << "\n\n";

		}
		catch (const exception& e) {
			cerr << "Exception: " << e.what() << "\n";
		}
		catch (...) {
			cerr << "Something went horribly wrong and you are a horrible person\n";
		}
	}
}

void test_parser() {
	DBParser parser;
	for (int i = 0; i < tests.size(); i++) {
		try {
			bool works = parser.execute_query(tests[i]);

			cout << "line: \"" << tests[i] << "\" is ";

			if (works) cout << "valid\n";
			else cout << "not valid\n";
		}
		catch (...) {
			cerr << "syntax error\n";
		}
	}

	
}

int main(){
	if(test_case == 1) test_tokenizer();
	else if(test_case == 2) test_parser();
	else if (test_case == 3) {
		test_tokenizer();
		test_parser();
	}

	cout << "enter 'exit'";
	string value;
	while (value != "exit") {
		cin >> value;
	}
	return 0;
}