#include "Database.h"



Database::Database()
{
}


Database::~Database()
{
}


// Query Functions
void Select(string view_name, string in_table_name, int row_index);
void Project(string view_name, string in_table_name, Attribute attributes);
void Rename(string view_name, string in_table_name, Attribute attributes);
void Set_union(string view_name, string table1_name, string table2_name);
void Set_difference(string view_name, string table1_name, string table2_name);
void Cross_product(string view_name, string table1_name, string table2_name);

// Command Functions

void Database::Close(string table_name){
	
};
void Database::Exit(){

};
void Database::Write(string table_name){
	Table new_table(table_name);
	Tables.push_back(new_table);

};
void Database::Open(string file_name){

};
void Database::Show(string table_name){
	for (int i = 0; i < Tables.size(); i++){
		if (Tables[i].Get_name() == table_name){
			Print_table(Tables[i]); //need to overload 
			break;
		}
	}
};
void Database::Create(string table_name, vector<Attribute> attribute_types, vector<Attribute> keys){
	Table new_table(table_name, attribute_types, keys)
	
};
void Database::Update(string relation_name, vector<string> attribute, vector<string> data, int row_index){

};
void Database::Insert_tuple(string relation_name, vector<string> tuple){

};
void Database::Insert_view(string relation_name, string view_name){

};
void Database::Remove(string table_name, int row_index){

};

// Utility Functions
int Database::Get_relation_index(string table_name){

};
int Database::Get_table_index(string table_name){

};
/*int Database::Get_attribute(TableType type, int table_index, string attribute_name){

};*/
void Database::Update_table_name(string new_name, string old_name){

};
Table Database::Get_table(string table_name){
	for (int i = 0; i < Tables.size(); i++){
		if (Tables[i].Get_name() == table_name){
			return Tables[i]; //need to overload 
			break;
		}
	}
};

void Database::Print_table(Table table_name){ //we need to overload the table operator
	cout << table_name;
};