#include "Database.h"
#include <fstream>
#include <iterator>

Database::Database()
{
}


Database::~Database()
{
}


// Query Functions
void Select(string view_name, string in_table_name, int row_index){

}
void Project(string view_name, string in_table_name, Attribute attributes){

}
void Rename(string view_name, string in_table_name, Attribute attributes){

}
void Set_union(string view_name, string table1_name, string table2_name){

}
void Set_difference(string view_name, string table1_name, string table2_name){

}
void Cross_product(string view_name, string table1_name, string table2_name){

}

// Command Functions

void Database::Close(string table_name){
	for (int i = 0; i<Tables.size();++i)
		if (table_name == Tables[i].Get_name()){
			Tables.erase(Tables.begin() + i);//Deletes index i begin() returns iterator
			break;//make sure to quit iterating because we change tables vec
		}
}
void Database::Exit(){

}
void Database::Write(string table_name){
	Table my_table=Get_table(table_name);
	ofstream out = ofstream((table_name+".db").c_str(), std::ofstream::out | std::ofstream::trunc);//trunc flag means content already in file will be deleted
	out << my_table;//Writes table to output stream
}
void Database::Open(string table_name){
	ifstream in = ifstream((table_name + ".db").c_str());
	if (!in.is_open())
		cerr << "could not open file" << table_name + ".db"<<endl;
	else{
		Table new_table = Table();
		new_table.Read(in);
		//TODO need to implement protection against duplicate tables of same name
		Tables.push_back(new_table);
	}
}
void Database::Show(string table_name){
	Get_table(table_name).Pretty_print(cout); //Pretty print, prints things nicer in the console
}
void Database::Create(string table_name,vector<string> attribute_names, vector<string> attribute_types, vector<string> keys){
	Table new_table=Table(table_name,attribute_names, attribute_types, keys);
	//TODO need to implement protection for multiple tables of the same name
	Tables.push_back(new_table);
}
void Database::Update(string relation_name, vector<string> attribute, vector<string> data, int row_index){

}
void Database::Insert_tuple(string relation_name, vector<string> tuple){

}
void Database::Insert_view(string relation_name, string view_name){

}
void Database::Delete(string table_name, int row_index){//renamed remove to delete to match project requirements

}

// Utility Functions
//no need for get_table_index(int), when you can Get_table(string)
//int Database::Get_table_index(string table_name){
//	for (int i = 0; i < Tables.size(); ++i)
//		if (table_name == Tables[i].Get_name())
//			return i;
//	cerr << "Table index not found\n";
//	return -1;
//}
/*int Database::Get_attribute(TableType type, int table_index, string attribute_name){

};*/
void Database::Update_table_name(string new_name, string old_name){
	bool found = false;
	for (int i = 0; i < Tables.size(); ++i)
		if (old_name == Tables[i].Get_name()){
			Tables[i].Set_name(new_name);
			found = true;
		}
	if (!found)
		cerr << "Matching table not renaming therefore impossible\n";
}
Table Database::Get_table(string table_name) const{
	for (int i = 0; i < Tables.size(); i++){
		if (Tables[i].Get_name() == table_name){
			return Tables[i];
		}
	}
	cerr << "Table NOT FOUND\n";
	return Table();//IF Table not found return default
}

Table Database::operator[](int i) const{
	if (i<0 || i>Tables.size()){
		cerr << "can not access Table, index out of range\n";
		return Table();
	}
	return Tables[i];
}

Table Database::operator[](string table_name) const{
	return Get_table(table_name);
}