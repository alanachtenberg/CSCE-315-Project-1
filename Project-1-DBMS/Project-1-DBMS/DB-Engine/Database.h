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

using namespace std;



class Database
{
private:
	vector<Table> Tables;
public:
	Database();
	~Database();

	//returns Tables vector
	vector<Table> get_Tables();

	// Query Functions
	Table Select(string view_name, string in_table_name, string attribute_name, Token_Type comparison, string value);
	Table Select(string view_name, Table in_table_name, string attribute_name, Token_Type comparison, string value);
	Table Select(string view_name, Table in_table_name, vector<int> true_conditions);
	Table Project(string view_name, string in_table_name, vector<string> attributes);
	Table Project(string view_name, Table in_table_name, vector<string> attributes);
	Table Rename(string new_name, string old_name, string in_table);
	Table Rename(string new_name, Table in_table_name, vector<string> new_names);
	Table Set_union(string view_name, string table1_name, string table2_name);
	Table Set_union(string view_name, Table table1_name, Table table2_name);
	Table Set_difference(string view_name, string table1_name, string table2_name);
	Table Set_difference(string view_name, Table table1_name, Table table2_name);
	Table Cross_product(string view_name, string table1_name, string table2_name);
	Table Cross_product(string view_name, Table table1_name, Table table2_name);

	// Command Functions
	void Close(string table_name);
	void Exit();
	void Write(string table_name);
	//
	void Write(Table table);
	Table Open(string table_name);
	void Show(string table_name);
	void Show(Table table);
	Table Create(string table_name,vector<string> attribute_names, vector<string> attribute_types, vector<string> keys);
	void Update(string table_name, vector<string> old_attributes, vector<string> new_values, string attribute_name, Token_Type comparison, string value);
	void Update(Table &table_name, vector<string> true_conditions, vector<pair<string, string>> new_values);
	void Insert(string table_name, vector<string> tuple);
	void Insert(string dest_table, Table source);//Insert FROM source_table INTO dest_table
	void Insert(Table &dest_table, Table source);
	void Insert(Table &dest_table, vector<string> new_tuple);
	void Delete(string table_name, string attribute_name, Token_Type comparison, string value);//renamed remove to delete to match project requirements
	void Delete(Table table_name, Attribute attribute_name, Token_Type comparison, string value);
	// Utility Functions
	
	

	//renames table with old_name to new_name
	void Update_table_name(string new_name, string old_name);

	//returns table by table name
	Table Get_table(string table_name) const;
	void  Set_table(Table& table);
	//returns vector of ints=i where, values[i] comparison value evaluates to true
	//can only handle a single comparison for now, need to be able to handle more complex comparisons like x==a&&y==b
	vector<int> Compare(vector<string> values, Token_Type comparison, string value);

	//access operators one with int index or with string table name
	Table operator[](int i) const;
	Table operator[](string table_name) const;
};

#endif