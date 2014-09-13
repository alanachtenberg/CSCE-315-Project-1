#pragma once

#ifndef Table_H
#define Table_H

#include "Attribute.h"

class Table
{
private:
	const string ENDTABLE = "ENDTABLE";
	string Name;
	vector<Attribute> Attributes;
	vector<string> Keys;
public:
	//Constructors
	Table();
	Table(string name, vector<Attribute> attributes);
	Table(string table_name, vector<string> attribute_names, vector<string> var_types, vector<string> key_names);
	Table(const Table& table);
	//Copy Assignment
	Table& operator = (const Table& table);

	//Getters, Setters
	string Get_name();
	void Set_name(string name);
	vector<Attribute> Get_attributes();
	void Set_attributes(vector<Attribute> attributes);

	//Utility functions
	int Get_width();
	int Get_max_height();

	//Gets row of table by creating a new vector and added each individual attribute value
	vector<string> Get_row(int index);
	
	//gets column by calling Get_data on appropriate attribute
	vector<string> Get_column(int index);

	//Read and Write functions, to store data in text files
	istream& Read(istream& is);
	ostream& Write(ostream& os);

	//Print function that looks better for the console
	ostream& Pretty_print(ostream& os);
	
	//operator that returns the ith Attribute in Attributes vector
	Attribute operator [] (int i) const;
};

//Input operator
istream& operator >> (istream& is, Table& t) ;

//Output operator
ostream& operator << (ostream& os, Table& t) ;

#endif