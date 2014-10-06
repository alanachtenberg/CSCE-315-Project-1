
#ifndef Table_H
#define Table_H

#include "Attribute.h"

class Table
{
private:
	const std::string ENDTABLE = "ENDTABLE";
	std::string Name;
	std::vector<Attribute> Attributes;
	std::vector<std::string> Keys;
public:
	//Constructors
	Table();
	Table(std::string name, std::vector<Attribute> attributes);
	Table(std::string table_name, std::vector<std::string> attribute_names, std::vector<std::string> var_types, std::vector<std::string> key_names);
	Table(const Table& table);
	//Copy Assignment
	Table& operator = (const Table& table);

	//Getters, Setters
	std::string Get_name() const;
	void Set_name(std::string name);
	std::vector<Attribute> Get_attributes() const;
	void Set_attributes(std::vector<Attribute> attributes);
	void Clear_attribute_data();
	//Utility functions
	unsigned int Get_width() const;
	unsigned int Get_max_height() const;
	bool Is_default();

	//Gets row of table by creating a new std::vector and added each individual attribute value
	std::vector<std::string> Get_row(unsigned int index);
	void Set_row(unsigned int row_index, std::vector<std::string> values);
	void Insert_row(std::vector<std::string> values);
	void Delete_row(unsigned int row_index);
	
	//gets column by calling Get_data on appropriate attribute
	std::vector<std::string> Get_column(unsigned int index);

	//Read and Write functions, to store data in text files
	std::istream& Read(std::istream& is);
	std::ostream& Write(std::ostream& os);

	//Print function that looks better for the console
	std::ostream& Pretty_print(std::ostream& os);
	
	//operator that returns the ith Attribute in Attributes std::vector
	Attribute& operator [] (unsigned int i);

	//operator that returns the attribute with name matching attribute_name
	Attribute& operator [] (std::string attribute_name);

};

//Input operator
std::istream& operator >> (std::istream& is, Table& t) ;

//Output operator
std::ostream& operator << (std::ostream& os, Table& t) ;

#endif