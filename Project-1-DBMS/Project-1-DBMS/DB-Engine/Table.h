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
	Table();
	~Table();

	
};

#endif