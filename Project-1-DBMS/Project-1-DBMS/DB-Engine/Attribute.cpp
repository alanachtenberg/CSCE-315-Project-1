#include "Attribute.h"

Attribute::Attribute(){
	Name = "DefaultName";
	VarType = "DefaultVarType";
	Data = vector<string>();
	for (int i = 0; i < 10; ++i){
		Data.push_back("DefaultData");
	}
}

Attribute::Attribute(string name, vector<string> data){
	Name = name;
	Data = data;
}

string Attribute::Get_name(){
	return Name;
}

void Attribute::Set_name(string name){
	Name = name;
}

string  Attribute::Get_vartype(){
	return VarType;
}

void  Attribute::Set_vartype(string vartype){
	VarType = vartype;
}

vector<string> Attribute::Get_data(){
	return Data;
}
void Attribute::Set_data(vector<string> data){
	Data = data;
}

//Read and Write
istream& Attribute::Read(istream& is){
	string temp;
	getline(is, Name, '\n');
	getline(is, VarType, '\n');
	Data = vector<string>();
	while (1){
		getline(is, temp, ';');
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
	os << ENDLIST << ";";
	return os;
}