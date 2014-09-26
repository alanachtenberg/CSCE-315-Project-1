#ifndef DBPARSER_H
#define DBPARSER_H

#include "Token_Stream.h"
#include "Database.h"

//TODO
//overload db.Close(), db.Open() to accept table
//get Create to return instance of table created


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

	bool selection(); 
	bool projection(); 
	bool rename(); 

	bool condition(); 
	bool conjunction(); 
	bool comparison(); 
	bool op(); 
	bool operand(); 

	//commands
	Parser_Table command(); //done

	Parser_Table open_cmd(); //done
	Parser_Table close_cmd(); //done
	Parser_Table write_cmd(); //done
	Parser_Table exit_cmd();  //done
	Parser_Table show_cmd(); //done
	Parser_Table create_cmd(); //done
	bool update_cmd(); 
	bool insert_cmd();
	bool delete_cmd(); 

	//data
	Parser_Table relation_name(); //done
	Parser_Table expr(); //done
	Parser_Table atomic_expr(); //done
	std::string attribute_name(); //done
	std::string type(); //done
	std::vector<std::vector<std::string> > typed_attribute_list(); //done
	std::vector<std::string> attribute_list(); //done
	Token literal();

};

#endif