#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include "Table.h"
#include <vector>

class Databse
{
public:
	Database();
	~Database();

	vector<Table> Tables;


};

#endif