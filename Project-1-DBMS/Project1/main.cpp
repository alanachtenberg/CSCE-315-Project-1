#include "Token_Stream.h"
#include "DBParser.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int test_case = 1;

void test_tokenizer() {
	ifstream ifs("test.txt");
	string line;
	int valid = 0, invalid = 0;

	while (getline(ifs, line)) {
		try {
			Token_stream ts(line);

			Token token = ts.get();
			cout << line << "\n";
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
	parser.execute_file("test.txt");
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