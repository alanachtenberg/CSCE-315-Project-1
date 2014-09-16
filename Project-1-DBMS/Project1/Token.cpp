#include "Token.h"

std::string Token_Type_Name[] = {
	"_lpar", "_rpar", "_plus", "_minus", "_multiply", "_divide", "_mod", "_assign", "_semicolon",
	"_quotation", "_comma", "_assign_eq",
	"_equals", "_not_eq", "_less", "_less_eq", "_greater", "_greater_eq",
	"_and", "_or",
	"_create", "_insert", "_select", "_project", "_show", "_rename",
	"_into", "_table", "_values", "_from", "_primary", "_key",
	"_relation", "_write", "_open", "_close", "_delete", "_update", "_set", "_where",
	"int_type", "_int_num", "_float_type", "_float_num", "_varchar", "_char", "_identifier",
	"_exit_program", "_null"
};