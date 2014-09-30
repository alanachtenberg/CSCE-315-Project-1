#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include "ComparisonTree.h"
#include "Table.h"
#include <vector>
#include <string>
#include <iostream>    
#include <iomanip>
#include <utility>

class Database
{
private:
	std::vector<Table> Tables;
public:
	Database();
	~Database();

	//returns Tables std::vector
	std::vector<Table> get_Tables();

	// Query Functions
	Table Select(Table& table, Comparison_tree *comparison);
	Table Project(Table& table, std::vector<std::string> attributes);
	Table Rename(Table& table, std::vector<std::string> new_names);
	Table Set_union(std::string view_name, Table table1_name, Table table2_name);
	Table Set_difference(Table& table1, Table& table2);
	Table Cross_product(Table& table1_name, Table& table2_name);

	// Command Functions
	void Close(std::string table_name);
	void Exit();
	Table Write(std::string table_name);
	Table Write(Table& table);
	Table Open(std::string table_name);
	void Show(std::string table_name);
	void Show(Table& table);
	Table Create(std::string table_name,std::vector<std::string> attribute_names, std::vector<std::string> attribute_types, std::vector<std::string> keys);
	Table Update(Table &table_name, Comparison_tree *comparison, std::vector<pair<std::string, std::string>> new_values);
	Table Insert(Table &dest_table, Table source);
	Table Insert(Table &dest_table, std::vector<std::string> new_tuple);
	Table Delete(Table &table_name, Comparison_tree *comparison);
	// Utility Functions
	
	

	//renames table with old_name to new_name
	void Update_table_name(std::string new_name, std::string old_name);

	//returns table by table name
	Table Get_table(std::string table_name) const;
	void  Set_table(Table& table);
	//returns std::vector of ints=i where, values[i] comparison value evaluates to true
	//can only handle a single comparison for now, need to be able to handle more complex comparisons like x==a&&y==b
	//std::vector<int> Compare(std::vector<std::string> values, Token_Type comparison, std::string value);

	//access operators one with int index or with std::string table name
	Table operator[](unsigned int i) const;
	Table operator[](std::string table_name) const;
};

#endif