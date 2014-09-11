

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Table.h"
using namespace std;
int main(){
	ofstream out;
	out.open("sample.txt");
	cout << "Hello DB Engine\n";

	vector<Attribute> myattributes;
	Attribute attribute = Attribute();
	myattributes.push_back(attribute);
	myattributes.push_back(attribute);
	Table mytable = Table();
	mytable.Set_attributes(myattributes);
	mytable.Write(out);
	out.close();
	ifstream in;
	in.open("sample.txt");
	mytable.Read(in);
	cout << "input anything to exit";
	string dummy;
	cin >> dummy;
	return 0;
}