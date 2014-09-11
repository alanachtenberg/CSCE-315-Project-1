#include "Table.h"


Table::Table()
{
	Name = "DefaultTableName";
	Attributes = vector<Attribute>();
}

Table::Table(string name, vector<Attribute> attributes){
	Name = name;
	Attributes = attributes;
}

Table::Table(Table& table){
	Name = table.Name;
	Attributes = table.Attributes;
}

Table::~Table()
{
}

string Table::Get_name(){
	return Name;
}
void Table::Set_name(string name){
	Name = name;
}
vector<Attribute> Table::Get_Attributes(){
	return Attributes;
}
void Table::Set_attributes(vector<Attribute> attributes){
	Attributes = attributes;
}