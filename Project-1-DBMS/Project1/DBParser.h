#ifndef DBPARSER_H
#define DBPARSER_H

#include "Token_Stream.h"

class DBParser {
public: 
	Token_stream ts;
	

private:
	bool program();

	bool query();
	bool command();

	//commands
	bool open_cmd();
	bool close_cmd();
	bool write_cmd();
	bool exit_cmd();
	bool show_cmd();
	bool create_cmd();
	bool update_cmd();
	bool insert_cmd();
	bool delete_cmd();

	//data structures
	bool relation_name();
	bool expr();
	bool atomic_expr();
	bool attribute_name();
	bool type();

	bool typed_attribute_list();
	bool attribute_list();

};

#endif