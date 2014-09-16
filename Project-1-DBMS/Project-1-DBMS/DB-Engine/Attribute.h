#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Attribute{
	private:
		const string ENDLIST = "ENDLIST"; //used to simplify Read function
		string Name;
		string VarType;
		vector<string> Data;
	public:
		//Constructors
		Attribute();
		Attribute(string name, string vartype, vector<string> data);
		Attribute(const Attribute& attribute);
		//Copy Assignment operator
		Attribute& operator = (const Attribute& attribute);
		
		//Getters and Setters
		
		string	Get_name() const;
		void  Set_name(string name);

		string  Get_vartype() const;
		void  Set_vartype(string vartype);
		
		void Clear_data();
		vector<string> Get_data() const;
		void Set_data( vector<string> data);

		string Get_value(int index) const;
		void Set_value(int index, string value);
		void Insert_value(string value);

		int Get_size() const;

		//Read and Write
		istream& Read(istream& is);
		ostream& Write(ostream& os);

		string& operator [](int i);
};



#endif