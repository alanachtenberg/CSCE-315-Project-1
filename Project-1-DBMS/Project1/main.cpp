#include "Token_Stream.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void test_tokenizer() {
	try {
		ifstream ifs("test.txt");

		Token_stream ts(ifs);

		vector<Token> tokens = ts.tokenize();

		for (int i = 0; i < tokens.size(); i++) {
			Token t = tokens[i];
			cout << " type: " << left << setw(15) << t.get_type_name() <<
				" name: " << left << setw(15) << t.get_name() <<
				" value: " << left << setw(15) << t.get_value() << "\n";
		}
	}
	catch (const exception& e) {
		cerr << "Exception: " << e.what() << "\n";
	}
	catch (...) {
		cerr << "Something went horribly wrong and you are a horrible person\n";
	}
}

int main(){
	test_tokenizer();

	cout << "enter 'exit'";
	string value;
	while (value != "exit") {
		cin >> value;
	}
	return 0;
}