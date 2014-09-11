#include "Table.h"
#include <algorithm>

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

int Table::Get_width(){
	return Attributes.size();
}
int Table::Get_max_height(){
	int max_height = 0;
	for (int i = 0; i < Attributes.size(); ++i)
		max(max_height, Attributes[i].Get_size());
	return max_height;
}

vector<string> Table::Get_row(int index){
	if (index<0 || index>Get_max_height()){
		cerr << "cannot get row, index out of range"<<endl;
		return vector<string>();
	}
	else
	{
		vector<string> new_vector = vector<string>();
		for (int i = 0; i < Get_width(); ++i)
			new_vector.push_back(Attributes[i].Get_data()[index]);
		return new_vector;
	}
}
vector<string> Table::Get_column(int index){
	if (index<0 || index>Get_width()){
		cerr << "cannot get column, index out of range" << endl;
		return vector<string>();
	}
	else
	{
		return Attributes[index].Get_data();
	}
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

//Input operator
istream& operator >> (istream& is, Table& t){
	t.Read(is);
	return is;
}

//Output operator
ostream& operator << (ostream& os, Table& t){
	t.Write(os);
	return os;
}