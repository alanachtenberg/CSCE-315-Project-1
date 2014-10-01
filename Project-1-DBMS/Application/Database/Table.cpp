#include "Table.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Table::Table()
{
	Name = "DefaultTableName";
	Attributes = vector<Attribute>();
	Keys = vector<string>();
}

Table::Table(string table_name, vector<string> attribute_names, vector<string> var_types, vector<string> key_names)
{
	Name = table_name;
	if (attribute_names.size() != var_types.size() || key_names.size() < 1){
		cerr << "Cannot constuct table, must have at least 1 key name, and # of attributes and variable types must be equal\n";
		return;
	}
	for ( unsigned int i = 0; i < attribute_names.size(); ++i){
		Attribute new_attribute = Attribute(attribute_names[i], var_types[i], vector<string>());
		Attributes.push_back(new_attribute);
	}
	Keys = key_names;
}

Table::Table(const Table& table){
	Name = table.Name;
	Attributes = table.Attributes;
	Keys = table.Keys;
}

Table& Table:: operator = (const Table& table){
	Name = table.Name;
	Attributes = table.Attributes;
	Keys = table.Keys;
	return *this;
}

string Table::Get_name()const{
	return Name;
}

void Table::Set_name(string name){
	Name = name;
}

vector<Attribute> Table::Get_attributes() const{
	return Attributes;
}

void Table::Set_attributes(vector<Attribute> attributes){
	Attributes = attributes;
}

void Table::Clear_attribute_data(){
	for ( unsigned int i = 0; i < Get_width(); i++){
		Attributes[i].Clear_data();
	}
}

unsigned int Table::Get_width() const{
	return Attributes.size();
}
unsigned int Table::Get_max_height() const{
	int max_height = 0;
	for ( unsigned int i = 0; i < Attributes.size(); ++i)
		if (Attributes[i].Get_size()>max_height)
			max_height = Attributes[i].Get_size();
	return max_height;
}

//checks to see 
bool Table::Is_default() {
	if (Name == "DefaultTableName") return true;
	else return false;
}

//returns a tuple in the form of a vector string of the data
vector<string> Table::Get_row(unsigned int index){
	if (index<0 || index>Get_max_height()){
		cerr << "cannot get row, index out of range"<<endl;
		return vector<string>();
	}
	else
	{
		vector<string> new_vector = vector<string>();
		for ( unsigned int i = 0; i < Get_width(); ++i) //loop through for each attribute in the table
			new_vector.push_back(Attributes[i][index]);
		return new_vector;
	}
}

//update a specific index with an updated tuple passed
void Table::Set_row(unsigned int row_index, vector<string> values){
	if (row_index<0 || row_index>Get_max_height())
		cerr << "cannot set row, index out of range" << endl;
	else// using else prevents action in case of error
	{
		if (values.size() != Attributes.size())
			cerr << "cannot set row, values vector does not match size of attributes vector" << endl;
		else
		{
			for ( unsigned int i = 0; i < values.size(); ++i)
				Attributes[i][row_index] = values[i];//Attributes[i] gets column, [row_index] gets data within column
		}
	}
}

//insert a new tuple into a table
void Table::Insert_row(vector<string> values){
	if (values.size() != Attributes.size())
		cerr << "cannot insert row, values vector does not match size of attributes vector" << endl;
	else
	{
		for ( unsigned int i = 0; i < values.size(); ++i) // loop for size of the row you're passing in
			Attributes[i].Insert_value(values[i]);// add the value of the particuler index of attribute to the new tuple
	}
}

//delete a new tuple from a table
void Table::Delete_row(unsigned int row_index){
	if (row_index<0 || row_index>Get_max_height())
		cerr << "cannot delete row, index out of range" << endl;
	else
	{
		for ( unsigned int i = 0; i < Get_width(); ++i){// delete each item in the data vector of the same index, essentially deleting the tuple
			vector<string> values=Attributes[i].Get_data();
			values.erase(values.begin() + row_index);//deletes data at row_index in vector
			Attributes[i].Set_data(values); //writes back new vector
		}
	}
}


//return a vector of data for a particular attribute
vector<string> Table::Get_column(unsigned int index){ //return a data vector of one particular attribute
	if (index<0 || index>Get_width()){
		cerr << "cannot get column, index out of range" << endl;
		return vector<string>();
	}
	else
	{
		return Attributes[index].Get_data();
	}
}

//read in a table from as a string stream
istream& Table::Read(istream& is){
	string temp_string;
	Attribute temp;
	getline(is, Name,'\n');
	Attributes = vector<Attribute>();
	while (1){ //allows to read in until there is no more values in the table, covering the entire table
		temp.Read(is);// assume there is always at least one attribute to read
		Attributes.push_back(temp);
		is >> temp_string;
		if (temp_string==ENDTABLE)
			break;
		else//putback the string so we can read it for the next attribute
			for ( unsigned int i = 0; i < temp_string.size(); ++i)
				is.putback(temp_string.c_str()[temp_string.size()-i-1]);// minus one to account for null terminator//put the characters back in the correct order, ie. from back to front
	}
	return is;
}

ostream& Table::Write(ostream& os){
	os << Name<<endl;
	for ( unsigned int i = 0; i < Attributes.size(); ++i){
		Attributes[i].Write(os);
	}
	os << ENDTABLE;
	return os;
}

//Print out in nice readable format
ostream& Table::Pretty_print(ostream& os){
	os << "------------------";
	os << Name << "------------------" << endl << endl;
	for ( unsigned int i = 0; i < Get_width(); ++i){
		os << Attributes[i].Get_name() << right << setw(20);
	}
	os << endl<<endl;
	for ( unsigned int j = 0; j < Get_max_height(); ++j){//loop through with the tables height
		vector<string> values = Get_row(j); // set the vector of strings equal to the tuple you're printing out
		for ( unsigned int k = 0; k < Get_width(); ++k){ //iterate through and print out each tuple on the line
			os << values[k]<< right<<setw(20);
		}
		os << endl;
	}
	os << "------------------------------------" << endl;
	return os;
}

Attribute& Table::operator [](unsigned int i){//use of const prevents operator from modifying Table or calling non const functions
	if (i<0 || i>=Attributes.size()){
		cerr << "error out of range access of Attributes\n";
			return Attribute();
	}
	else{
		return Attributes[i];
	}
}

Attribute& Table::operator [](string attribute_name){
	for ( unsigned int i = 0; i < Attributes.size(); ++i){//linear search for attribute with matching name
		if (Attributes[i].Get_name() == attribute_name)
			return Attributes[i];
	}
	cerr << "error access unsuccessful, [" << attribute_name << "]\n";
	return Attribute();// return default value and inform of error
}


//Input operator
istream& operator >>  (istream& is, Table& t){
	t.Read(is);
	return is;
}

//Output operator
ostream& operator <<  (ostream& os, Table& t){
	t.Write(os);
	return os;
}