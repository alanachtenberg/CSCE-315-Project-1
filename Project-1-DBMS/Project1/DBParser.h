#ifndef DBPARSER_H
#define DBPARSER_H

#include "Token_Stream.h"
#include "Database.h"

class DBParser {
	Token_stream* ts;
	Database db;
	
public: 
	DBParser() {};

	bool execute_query(std::string query);
	void execute_file(std::string filename);
	
private:
	//entry point
	bool program(); 

	//queries
	bool query(); 

	bool selection(); 
	bool projection(); 
	bool rename(); 
	bool set_union(); 
	bool difference(); 
	bool product(); 

	bool condition(); 
	bool conjunction(); 
	bool comparison(); 
	bool op(); 
	bool operand(); 

	//commands
	bool command(); 

	bool open_cmd(); //done
	bool close_cmd(); //done
	bool write_cmd(); //done
	bool exit_cmd();  //done
	bool show_cmd(); 
	bool create_cmd(); //done
	bool update_cmd(); 
	bool insert_cmd();
	bool delete_cmd(); 

	//data
	std::string relation_name(); //done
	bool expr(); 
	bool atomic_expr(); 
	std::string attribute_name(); //done
	std::string type(); //done
	std::vector<std::vector<std::string> > typed_attribute_list(); //done
	std::vector<std::string> attribute_list(); //done
	Token literal();

};

#endif