#include "DBParser.h"
#include <fstream>
#include <iostream>

using namespace std;

void test_parser() {
	
}

int main(){
	DBParser parser;
	parser.execute_file("final_test.txt");
	/*try {
		Token_stream ts("select -2.1 \"this is an example of a literal\"");
		Token token;
		token = ts.get();
		cout << token.get_type_name() << " " << token.get_value() << " " << token.get_name() << "\n";

		token = ts.get();
		cout << token.get_type_name() << " " << token.get_value() << " " << token.get_name() << "\n";

		token = ts.get();
		cout << token.get_type_name() << " " << token.get_value() << " " << token.get_name() << "\n";
	}
	catch (BadTokenException e) {
		cout << e.what();
	}
	system("pause");*/
}