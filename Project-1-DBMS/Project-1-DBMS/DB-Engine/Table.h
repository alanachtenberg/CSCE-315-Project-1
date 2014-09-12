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

public:
	//Constructors
	Table();
	Table(string name, vector<Attribute> attributes);
	Table(string table_name, vector<Attribute> attributes, vector<Attribute> key);
	Table(string table_name);
	Table(const Table& table);
	//Copy Assignment
	Table& operator = (const Table& table);

	//Getters, Setters
	string Get_name();
	void Set_name(string name);
	vector<Attribute> Get_Attributes();
	void Set_attributes(vector<Attribute> attributes);

	//Utility functions
	int Get_width();
	int Get_max_height();

	vector<string> Get_row(int index);
	vector<string> Get_column(int index);
	//Read and Write functions
	istream& Read(istream& is);
	ostream& Write(ostream& os);
};

//Input operator
istream& operator >> (istream& is, Table& t);

//Output operator
ostream& operator << (ostream& os, Table& t);

#endif