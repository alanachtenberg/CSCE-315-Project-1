#include "Table.h"
#include <algorithm>
#include <iomanip>

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
	for (int i = 0; i < attribute_names.size(); ++i){
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
	for (int i = 0; i < Get_width(); i++){
		Attributes[i].Clear_data();
	}
}

int Table::Get_width() const{
	return Attributes.size();
}
int Table::Get_max_height() const{
	int max_height = 0;
	for (int i = 0; i < Attributes.size(); ++i)
		if (Attributes[i].Get_size()>max_height)
			max_height = Attributes[i].Get_size();
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
			new_vector.push_back(Attributes[i][index]);
		return new_vector;
	}
}

void Table::Set_row(int row_index, vector<string> values){
	if (row_index<0 || row_index>Get_max_height())
		cerr << "cannot set row, index out of range" << endl;
	else// using else prevents action in case of error
	{
		if (values.size() != Attributes.size())
			cerr << "cannot set row, values vector does not match size of attributes vector" << endl;
		else
		{
			for (int i = 0; i < values.size(); ++i)
				Attributes[i][row_index] = values[i];//Attributes[i] gets column, [row_index] gets data within column
		}
	}
}

void Table::Insert_row(vector<string> values){
	if (values.size() != Attributes.size())
		cerr << "cannot insert row, values vector does not match size of attributes vector" << endl;
	else
	{
		for (int i = 0; i < values.size(); ++i)
			Attributes[i].Insert_value(values[i]);
	}
}

void Table::Delete_row(int row_index){
	if (row_index<0 || row_index>Get_max_height())
		cerr << "cannot delete row, index out of range" << endl;
	else
	{
		for (int i = 0; i < Get_width(); ++i){
			vector<string> values=Attributes[i].Get_data();
			values.erase(values.begin() + row_index);//deletes data at row_index in vector
		}
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
	getline(is, Name,'\n');
	Attributes = vector<Attribute>();
	while (1){
		temp.Read(is);// assume there is always at least one attribute to read
		Attributes.push_back(temp);
		is >> temp_string;
		if (temp_string==ENDTABLE)
			break;
		else//putback the string so we can read it for the next attribute
			for (int i = 0; i < temp_string.size(); ++i)
				is.putback(temp_string.c_str()[temp_string.size()-i-1]);// minus one to account for null terminator//put the characters back in the correct order, ie. from back to front
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

ostream& Table::Pretty_print(ostream& os){
	os << Name << endl << endl;
	for (int i = 0; i < Get_width(); ++i){
		os << Attributes[i].Get_name() << right << setw(20);
	}
	os << endl<<endl;
	for (int j = 0; j < Get_max_height(); ++j){
		vector<string> values = Get_row(j);
		for (int k = 0; k < Get_width(); ++k){
			os << values[k]<< right<<setw(20);
		}
		os << endl;
	}
	return os;
}

Attribute& Table::operator [](int i){//use of const prevents operator from modifying Table or calling non const functions
	if (i<0 || i>Attributes.size()){
		cerr << "error out of range access of Attributes\n";
			return Attribute();
	}
	else{
		return Attributes[i];
	}
}

Attribute& Table::operator [](string attribute_name){
	for (int i = 0; i < Attributes.size(); ++i){//linear search for attribute with matching name
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