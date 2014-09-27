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
	Parser_Table program(); 

	//queries
	Parser_Table query(); 

	Parser_Table selection(); 
	Parser_Table projection();
	Parser_Table rename(); 

	Comparison_tree condition(); 
	Comparison_tree conjunction(); 
	Comparison_tree comparison(); 
	Token op();
	std::string operand(); 

	//commands
	Parser_Table command(); 

	Parser_Table open_cmd(); 
	Parser_Table close_cmd(); //working
	Parser_Table write_cmd(); 
	Parser_Table exit_cmd();  
	Parser_Table show_cmd(); 
	Parser_Table create_cmd(); //working
	Parser_Table update_cmd(); 
	Parser_Table insert_cmd(); //working
	Parser_Table delete_cmd(); 

	//data
	Parser_Table relation_name(); 
	Parser_Table expr(); 
	Parser_Table atomic_expr(); 
	std::string attribute_name(); 
	std::string type(); 
	std::vector<std::vector<std::string> > typed_attribute_list(); 
	std::vector<std::string> attribute_list(); 
	std::string literal();

};

#endif