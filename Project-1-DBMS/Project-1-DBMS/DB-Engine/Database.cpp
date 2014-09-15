#include "Database.h"
#include <fstream>
#include <iterator>
Database::Database()
{
}


Database::~Database()
{
}

vector<Table> Database::get_Tables(){
	return Tables;
}
// Query Functions
//need someone to computer comparisons before they are sent to the select function
//ie. some seperate operator functions we can pass into the select function
Table Database::Select(string view_name, string in_table_name, string attribute_name, Token_Type comparison, string value){
	



	Table my_table = Get_table(in_table_name);
	Table new_table = Table(my_table);
	new_table.Clear_attribute_data();

	Attribute my_attribute = my_table[attribute_name];
	vector<int> row_indicies = Compare(my_attribute.Get_data(), comparison, value);//Gets a vector of rows that match comparison
	for (unsigned int i = 0; i < row_indicies.size(); i++){
		new_table.Insert_row(my_table.Get_row(row_indicies[i]));
	}
	return new_table;
}
void Database::Project(string view_name, string in_table_name, vector<string> attributes){
	Table my_table = Get_table(in_table_name);
	vector<Attribute> projected;
	for (int i = 0; i < attributes.size(); i++){
		projected.push_back(my_table[attributes[i]]);

	}
	Table new_table;
	new_table.Set_name(view_name);
	new_table.Set_attributes(projected);
}
void Rename(string new_name, string old_name, Table table){
	int num_attr;
	num_attr = table.Get_width();       // Number of columns in table
	bool check = false;

	for (int i = 0; i < num_attr; ++i){
		if (table[i].Get_name() == old_name){
			cout << "Old name found" << endl;
			table[i].Set_name(new_name);
			check = true;
		}
	}
	if (check != true){
		cerr << "Error during Rename (could not find existing name)" << endl;
	}
}

void Database::Set_union(string view_name, string table1_name, string table2_name){

	Table new_table = Get_table(table1_name);//new table includes table 1 values
	Table table2 = Get_table(table2_name);

	// Check to see if each relation has same number of attributes
	int num_attr1, num_attr2;
	num_attr1 = new_table.Get_width();
	num_attr2 = table2.Get_width();
	if (num_attr1 != num_attr2)
		cerr << "Error during set union (different number of attributes)" << endl;

	// Check to make sure the attributes are the same in each table
	for (int i = 0; i < num_attr1; ++i){
		if (new_table[i].Get_name() != table2[i].Get_name())
			cerr << " Error during set union (attributes do not match)" << endl;
	}

	for (int i = 0; i < table2.Get_max_height(); ++i){
		bool found = false;
		vector<string> row = table2.Get_row(i);
		for (int j = 0; j < new_table.Get_max_height(); ++j)
			if (row == new_table.Get_row(j))
				found = true;
		if (!found)
			new_table.Insert_row(row);
	}
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
	cout << "Closing DBMS" << endl;
	std::exit(0); 
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

void Database::Update(string table_name, vector<string> old_attributes, vector<string> new_values, string attribute_name, Token_Type comparison, string value){
	if (old_attributes.size() != new_values.size())
		cerr << "cant update, attribute list size does not match # of new values" << endl;
	else{
		Table my_table = Get_table(table_name);
		Attribute comparison_attribute = my_table[attribute_name];

		vector<int> row_indicies = Compare(comparison_attribute.Get_data(), comparison, value);

		for (int i = 0; i < row_indicies.size(); ++i)
			for (int j = 0; j < old_attributes.size(); ++j)
				my_table[old_attributes[j]][row_indicies[i]]=new_values[j]; //old_attibutes[j] is attribute name, row_indicies[i] is the index of data to replace

	}
}
void Database::Insert(string table_name, vector<string> tuple){
	Table my_table = Get_table(table_name);
	if (my_table.Get_width() != tuple.size())
		cerr << "Cant insert Tuple, size of tuple does not match table" << endl;
	else
	{
		for (int i = 0; i < my_table.Get_width(); ++i)
			my_table.Insert_row(tuple);
	}

}
void Database::Insert(string dest_table, string source_table){
	Table dest = Get_table(dest_table);
	Table source = Get_table(source_table);
	if (dest.Get_width() != source.Get_width())
		cerr << "Can not insert from source table to dest table, table width does not match" << endl;
	else
	{
		for (int i = 0; i < source.Get_max_height(); ++i)
			dest.Insert_row(source.Get_row(i));
	}


}

//can only handle a single comparison for now, need to be able to handle Where x==a&&y==b
void Database::Delete(string table_name, string attribute_name ,Token_Type comparison, string value){//renamed remove to delete to match project requirements
	Table my_table = Get_table(table_name);
	Attribute my_attribute = my_table[attribute_name];

	vector<int> row_indicies=Compare(my_attribute.Get_data(), comparison, value);//Gets a vector of rows that match comparison

	for (int i = 0; i < row_indicies.size(); ++i)
		my_table.Delete_row(row_indicies[i]);
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
//returns Tables vector


void Database::Update_table_name(string new_name, string old_name){
	bool found = false;
	for (int i = 0; i < Tables.size(); ++i)
		if (old_name == Tables[i].Get_name()){
			Tables[i].Set_name(new_name);
			found = true;
		}
	if (!found)
		cerr << "Matching table not found, renaming therefore impossible\n";
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

//returns vector of row index where, (values[i] comparison value) evaluates to true
vector<int> Database::Compare(vector<string> values, Token_Type comparison, string value){
	vector<int> hits = vector<int>();//vector of indicies that return true for comparison
	for (int i = 0; i < values.size(); ++i){	
		switch (comparison)//
		{
		case Token_Type::_equals:
			if (values[i] == value)
				hits.push_back(i);
			break;
		case Token_Type::_not_eq:
			if (values[i] != value)
				hits.push_back(i);
			break;
		case Token_Type::_less:
			if (values[i] < value)
				hits.push_back(i);
			break;
		case Token_Type::_less_eq:
			if (values[i] <= value)
				hits.push_back(i);
			break;
		case Token_Type::_greater:
			if (values[i] > value)
				hits.push_back(i);
			break;
		case Token_Type::_greater_eq:
			if (values[i] >= value)
				hits.push_back(i);
			break;
		default:
			cerr << "error comparison type unknown"<<endl;
				break;
		}
	}
	return hits;
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