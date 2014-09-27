#ifndef DBPARSER_H
#define DBPARSER_H

#include "Token_Stream.h"
#include "Database.h"

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

	Parser_Table selection(); //done, needs API change
	Parser_Table projection(); //done
	Parser_Table rename(); //done, need API change

	Comparison_tree condition(); //done
	Comparison_tree conjunction(); //done
	Comparison_tree comparison(); //done
	Token op(); //done 
	std::string operand(); //done

	//commands
	Parser_Table command(); //done

	Parser_Table open_cmd(); //done
	Parser_Table close_cmd(); //done
	Parser_Table write_cmd(); //done
	Parser_Table exit_cmd();  //done
	Parser_Table show_cmd(); //done
	Parser_Table create_cmd(); //done
	Parser_Table update_cmd(); //done
	Parser_Table insert_cmd();
	Parser_Table delete_cmd(); 

	//data
	Parser_Table relation_name(); //done
	Parser_Table expr(); //done
	Parser_Table atomic_expr(); //done
	std::string attribute_name(); //done
	std::string type(); //done
	std::vector<std::vector<std::string> > typed_attribute_list(); //done
	std::vector<std::string> attribute_list(); //done
	std::string literal();

};

#endif