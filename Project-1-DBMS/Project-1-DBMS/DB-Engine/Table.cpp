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

Table::Table(const Table& table){
	Name = table.Name;
	Attributes = table.Attributes;
}

Table& Table:: operator = (const Table& table){
	return *this;
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

istream& Table::Read(istream& is){
	string temp_string;
	Attribute temp;
	getline(is, Name, '\n');
	Attributes = vector<Attribute>();
	while (1){
		temp.Read(is);// assume there is always at least one attribute to read
		Attributes.push_back(temp);
		is >> temp_string;
		if (temp_string==ENDTABLE)
			break;
		else//putback the string so we can read it for the next attribute
			for (int i = 0; i < temp_string.size(); ++i)
				is.putback(temp_string.c_str()[temp_string.size()-i]);//put the characters back in the correct order, ie. from back to front
	}
	return is;
}

ostream& Table::Write(ostream& os){
	os << Name<<endl;
	for (int i = 0; i < Attributes.size(); ++i){
		Attributes[i].Write(os);
	}
	os << ENDTABLE;
	return os;
}