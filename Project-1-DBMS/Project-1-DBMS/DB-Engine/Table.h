#pragma once

#ifndef Table_H
#define Table_H

#include "Attribute.h"
#include <vector>

class Table
{
public:
	Table();
	~Table();

	string Name;
	vector<Attribute> Attributes;
};

#endif