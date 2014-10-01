#ifndef DBPARSER_H
#define DBPARSER_H

#include "Token.h"
#include "Token_Stream.h"
#include "ComparisonTree.h"
#include "Table.h"
#include "Database.h"
#include <fstream>
#include <iostream>

//TODO
//get Create to return instance of table created
//need new APIs: Select(Table, condition), Rename(Table, vector<string>)
//Insert() needs to accept vector of strings

struct Parser_Table {
	Table table;
	bool valid;
};

class DBParser {
	Token_stream* ts;
	Database db;
	
public: 
	DBParser() {};

	Table execute_query(std::string query);
	void execute_file(std::string filename);
	
private:
	//entry point
	Parser_Table program(); //working

	//queries
	Parser_Table query(); //working

	Parser_Table selection(); //working
	Parser_Table projection(); //working
	Parser_Table rename(); //working

	Comparison_tree* condition(); //working
	Comparison_tree* conjunction(); //working
	Comparison_tree* comparison(); //working
	Token op(); //working
	std::string operand(); //working 

	//commands
	Parser_Table command(); //working

	Parser_Table open_cmd(); //working
	Parser_Table close_cmd(); //working
	Parser_Table write_cmd(); //working
	Parser_Table exit_cmd();  //working
	Parser_Table show_cmd();  //working
	Parser_Table create_cmd(); //working
	Parser_Table update_cmd(); //working
	Parser_Table insert_cmd(); //working
	Parser_Table delete_cmd(); //working

	//data
	Parser_Table relation_name(); //working
	Parser_Table expr(); //working
	Parser_Table atomic_expr(); //working
	std::string attribute_name(); //working 
	std::string type(); //working
	std::vector<std::vector<std::string> > typed_attribute_list(); //working
	std::vector<std::string> attribute_list(); //working
	std::string literal(); //working

};

#endif