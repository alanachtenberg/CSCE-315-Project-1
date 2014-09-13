#include "Attribute.h"

Attribute::Attribute(){
	Name = "DefaultName";
	VarType = "DefaultVarType";
	Data = vector<string>();
	for (int i = 0; i < 10; ++i){
		Data.push_back("DefaultData");
	}
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

vector<string> Attribute::Get_data() const{
	return Data;
}
void Attribute::Set_data(vector<string> data){
	Data = data;
}
string Attribute::Get_value(int index) const{
	if (index<0 || index>Data.size())
		cerr << "can not get attribute value, index out of range" << endl;
	else
		return Data[index];
	return "default";
}
int Attribute::Get_size() const{
	return Data.size();
}

//Read and Write
istream& Attribute::Read(istream& is){
	string temp;
	getline(is, Name, '\n');
	getline(is, VarType, '\n');
	Data = vector<string>();
	while (1){
		getline(is, temp, ';');//assumer there is always at least one value stored
		if (temp == ENDLIST)
			break;
		Data.push_back(temp);
	}
	return is;
}
ostream& Attribute::Write(ostream& os){
	os << Name << endl;
	os << VarType << endl;
	for (int i = 0; i < Data.size(); ++i)
		os << Data[i]<< ";";
	os << ENDLIST << ";\n";
	return os;
}

string Attribute::operator[](int i){
	if (i<0 || i>Data.size()){
		cerr << "Out of range access of data\n";
		return "Default";
	}
	else{
		return Data[i];
	}

}
