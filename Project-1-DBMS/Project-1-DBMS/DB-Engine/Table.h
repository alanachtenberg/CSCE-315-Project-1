#pragma once

#ifndef Table_H
#define Table_H

#include "Attribute.h"
#include <vector>

class Table
{
private:
	string Name;
	vector<Attribute> Attributes;
public:
	//Constructors
	Table();
	Table(string name, vector<Attribute> attributes);
	Table(Table& table);

	~Table();

	//Getters, Setters
	string Get_name();
	void Set_name(string name);
	vector<Attribute> Get_Attributes();
	void Set_attributes(vector<Attribute> attributes);

};

#endif