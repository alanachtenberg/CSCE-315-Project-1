#ifndef DBPARSER_H
#define DBPARSER_H

#include "Token_Stream.h"

class DBParser {
	Token_stream* ts;
public: 
	DBParser() {};

	bool execute_query(std::string query);
	

private:
	//entry point
	bool program(); //done

	//queries
	bool query(); //done

	bool selection(); //done
	bool projection(); //done
	bool rename(); //done
	bool set_union(); //done
	bool difference(); //done
	bool product(); //done

	bool condition(); //done
	bool conjunction(); //done
	bool comparison(); //done
	bool op(); //done
	bool operand(); //done

	//commands
	bool command(); //done

	bool open_cmd(); //done
	bool close_cmd(); //done
	bool write_cmd(); //done
	bool exit_cmd(); //done
	bool show_cmd(); //done
	bool create_cmd(); //done
	bool update_cmd(); //done
	bool insert_cmd();
	bool delete_cmd(); //done

	//data
	bool relation_name(); //done
	bool expr(); //done
	bool atomic_expr(); //done
	bool attribute_name(); //done
	bool type(); //done
	bool typed_attribute_list(); //done
	bool attribute_list(); //done
	bool literal();

};

#endif