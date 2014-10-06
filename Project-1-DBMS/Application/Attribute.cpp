#include "Attribute.h"
#include <iostream>
#include <string>

using namespace std;

Attribute::Attribute(){
	Name = "DefaultName";
	VarType = "DefaultVarType";
	Data = vector<string>();
}

Attribute::Attribute(string name, string vartype, vector<string> data){
	Name = name;
	VarType = vartype;
	Data = data;
}

Attribute::Attribute(const Attribute& attribute){
	Name = attribute.Name;
	VarType = attribute.VarType;
	Data = attribute.Data;
}

Attribute& Attribute::operator = (const Attribute& attribute){
	Name = attribute.Name;
	VarType = attribute.VarType;
	Data = attribute.Data;
	return *this;
}

string Attribute::Get_name() const{
	return Name;
}

void Attribute::Set_name(string name){
	Name = name;
}

string  Attribute::Get_vartype() const{
	return VarType;
}

void  Attribute::Set_vartype(string vartype){
	VarType = vartype;
}

void Attribute::Clear_data(){
	Data.clear();
}

vector<string> Attribute::Get_data() const{
	return Data;
}
void Attribute::Set_data(vector<string> data){
	Data = data;
}
string Attribute::Get_value(unsigned int index) const{
	if (index<0 || index>Data.size())
		cerr << "can not get attribute value, index out of range" << endl;
	else
		return Data[index];
	return "default";
}

void Attribute::Set_value(unsigned int index, string value){
	if (index<0 || index>Data.size())
		cerr << "can not set attribute value, index out of range" << endl;
	else
		Data[index] = value;
}
void Attribute::Insert_value(string value){
	Data.push_back(value);
}


int Attribute::Get_size() const{
	return Data.size();
}

//Read and Write
istream& Attribute::Read(istream& is){ //Reading in the attrbute from string stream
	string temp;
	getline(is, Name, '\n'); //first line is the name
	getline(is, VarType, '\n'); //second is the variable type
	Data = vector<string>();
	while (1){
		getline(is, temp, ';');//assumer there is always at least one value stored
		if (temp == ENDLIST)
			break;
		Data.push_back(temp); //pushing read data to data vector
	}
	return is;
}
ostream& Attribute::Write(ostream& os){ //outputting our attributes to a stream
	os << Name << endl;
	os << VarType << endl;
	for ( unsigned int i = 0; i < Data.size(); ++i) //running through the vector of data to output
		os << Data[i]<< ";";
	os << ENDLIST << ";\n";
	return os;
}

string& Attribute::operator[](unsigned int i){ //overloading the [] operator in order to access the data point from the attribute directly
	if (i<0 || i>=Data.size()){
		cerr << "Out of range access of data\n";
		return string("Default"); //error checking
	}
	else{
		return Data[i];
	}

}
