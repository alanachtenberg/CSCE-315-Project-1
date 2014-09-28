#include "DBParser.h"
#include <fstream>
#include <iostream>

using namespace std;

void test_parser() {
	DBParser parser;
	parser.execute_file("final_test.txt");
}

int main(){
	test_parser();
	

	cout << "enter 'exit'";
	string value;
	while (value != "exit") {
		cin >> value;
	}
	return 0;
}