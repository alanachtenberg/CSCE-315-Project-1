#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Attribute{
	private:
		const string ENDLIST = "ENDLIST";

		string Name;
		string VarType;
		vector<string> Data;
	public:

		Attribute();
		Attribute(string Name, vector<string> Data);

		string	Get_name();
		void  Set_name(string name);

		string  Get_vartype();
		void  Set_vartype(string vartype);

		vector<string> Get_data();
		void Set_data( vector<string> data);

		//Read and Write
		istream& Read(istream& is);
		ostream& Write(ostream& os);


};

#endif