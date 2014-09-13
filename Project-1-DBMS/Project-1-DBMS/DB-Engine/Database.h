#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include "Table.h"
#include <vector>
#include <string>
#include <iostream>    
#include <iomanip>

using namespace std;

class Database
{
private:
	vector<Table> Tables;
public:
	Database();
	~Database();

	

	// Query Functions
	void Select(string view_name, string in_table_name, int row_index);
	void Project(string view_name, string in_table_name, Attribute attributes);
	void Rename(string view_name, string in_table_name, Attribute attributes);
	void Set_union(string view_name, string table1_name, string table2_name);
	void Set_difference(string view_name, string table1_name, string table2_name);
	void Cross_product(string view_name, string table1_name, string table2_name);

	// Command Functions
	void Close(string table_name);
	void Exit();
	void Write(string table_name);
	void Open(string file_name);
	void Show(string table_name);
	void Create(string table_name,vector<string> attribute_names, vector<string> attribute_types, vector<string> keys);
	void Update(string table_name, vector<string> attribute, vector<string> data, int row_index);
	void Insert_tuple(string relation_name, vector<string> tuple);
	void Insert_view(string relation_name, string view_name);
	void Remove(string table_name, int row_index);

	// Utility Functions
	int Get_relation_index(string table_name);
	int Get_table_index(string table_name);
	//int Get_attribute(TableType type, int table_index, string attribute_name);
	void Update_table_name(string new_name, string old_name);
	Table Get_table(string table_name);
	void Print_table(Table table_name);
};

#endif