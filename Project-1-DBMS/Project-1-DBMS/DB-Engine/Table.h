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
	Table(const Table& table);
	//Copy Assignment
	Table& operator = (const Table& table);

	//Getters, Setters
	string Get_name();
	void Set_name(string name);
	vector<Attribute> Get_Attributes();
	void Set_attributes(vector<Attribute> attributes);

	//Read and Write functions
	istream& Read(istream& is);
	ostream& Write(ostream& os);
};

#endif