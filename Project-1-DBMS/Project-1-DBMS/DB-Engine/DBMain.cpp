

#include <stdio.h>
#include <iostream>
#include "Attribute.h"
#include <fstream>
using namespace std;
int main(){
	ofstream out;
	out.open("sample.txt");
	cout << "Hello DB Engine\n";
	Attribute myattribute = Attribute();
	myattribute.Write(out);
	out.close();
	ifstream in;
	in.open("sample.txt");
	myattribute.Read(in);
	return 0;
}