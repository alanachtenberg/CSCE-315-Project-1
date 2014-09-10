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

	// Query Functions
	void Select(string view_name, string in_table_name, int row_index);
	void Project(string view_name, string in_table_name, vector<string> attributes);
	void Rename(string view_name, string in_table_name, vector<string> attributes);
	void Set_union(string view_name, string table1_name, string table2_name);
	void Set_difference(string view_name, string table1_name, string table2_name);
	void Cross_product(string view_name, string table1_name, string table2_name);

	// Command Functions
	void Close(string table_name);
	void Exit();
	void Write(string table_name);
	void Open(string file_name);
	void Show(string table_name);
	void Create(string table_name, vector<string> attributes, vector<string> attribute_types, vector<string> keys);
	void Update(string relation_name, vector<string> attribute, vector<string> data, int row_index);
	void Insert_tuple(string relation_name, vector<string> tuple);
	void Insert_view(string relation_name, string view_name);
	void Remove(string table_name, int row_index);

	// Utility Functions
	int get_relation_index(string table_name);
	int get_view_index(string table_name);
	int get_attribute_index(TableType type, int table_index, string attribute_name);
	void update_view_name(string new_name, string old_name);
};

#endif