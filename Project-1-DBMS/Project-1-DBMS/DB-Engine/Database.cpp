#include "Database.h"
#include "ComparisonTree.h"
#include <fstream>
#include <iostream>
#include <string>
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
Table Database::Select(string view_name, string in_table_name, Comparison_tree *comparison){
	
	Table my_table = Get_table(in_table_name);
	Table new_table = Table(my_table);					// gets copy of my_table including attribute names
	new_table.Clear_attribute_data();					// clears old data

	vector<int> row_indicies = comparison->Eval_tree(my_table);		// vector of row indicies from my_table we want to insert into new_table
	for (unsigned int i = 0; i < row_indicies.size(); i++){
		new_table.Insert_row(my_table.Get_row(row_indicies[i]));	// Insert rows from my_table, at index of (row_indicies[i]), into new_table 
	}
	new_table.Set_name(view_name);									// Name new table 
	return new_table;
}


//Can take in a Table source and a condition index of the my_table source
//Takes the vector of indicies and loops through the tuples, inserting them into the new_table
Table Database::Select(Table &in_table_name, Comparison_tree *comparison){

	Table new_table = Table(in_table_name);			// gets copy of in_table_name including attribute names
	new_table.Clear_attribute_data();				// clears old data

	vector<int> row_indicies = comparison->Eval_tree(in_table_name);	// vector of row indicies from in_table_name we want to insert into new_table

	for (unsigned int i = 0; i < row_indicies.size(); i++){
		new_table.Insert_row(in_table_name.Get_row(row_indicies[i]));	//Gets tuple index from the true_conditions comparison list and inserts the tuples into the new_table
	}
	new_table.Set_name(in_table_name.Get_name());					// Name new table
	return new_table;
}

Table Database::Project(string view_name, string in_table_name, vector<string> attributes){
	Table my_table = Get_table(in_table_name);
	vector<Attribute> projected;
	for ( unsigned int i = 0; i < attributes.size(); i++){
		projected.push_back(my_table[attributes[i]]);

	}
	Table new_table;
	new_table.Set_name(view_name);
	new_table.Set_attributes(projected);
	
	return new_table;
}

Table Database::Project(string view_name, Table in_table_name, vector<string> attributes){
	Table my_table = Table(in_table_name);
	vector<Attribute> projected;
	for ( unsigned int i = 0; i < attributes.size(); i++){
		projected.push_back(my_table[attributes[i]]);

	}
	Table new_table;
	new_table.Set_name(view_name);
	new_table.Set_attributes(projected);
	return new_table;
}

Table Database::Rename(string new_name, string old_name, string in_table){
	Table table = Get_table(in_table);
	
	unsigned int num_attr;
	num_attr = table.Get_width();       // Number of columns in table
	bool check = false;

	for ( unsigned int i = 0; i < num_attr; ++i){
		if (table[i].Get_name() == old_name){
			cout << "Old name found" << endl;
			table[i].Set_name(new_name);
			check = true;
		}
	}
	if (!check){
		cerr << "Error during Rename (could not find existing name)" << endl;
	}
	Set_table(table);//updates table vector, not sure if this is correct implementation of grammar
	return table;
}

Table Database::Rename(string view_name, Table in_table_name, vector<string> new_names){
	Table new_table = Table(in_table_name);

	unsigned int num_attr;
	num_attr = new_table.Get_width();       // Number of columns in table
	bool check = false;

	for ( unsigned int i = 0; i < num_attr; ++i){
		new_table[i].Set_name(new_names[i]);// takes the new attribute name from the vector and sets it to the equal index in new_table attribute list
	}
	Set_table(new_table);//adds new_table to database
	return new_table;
}

Table Database::Set_union(string view_name, string table1_name, string table2_name){

	Table new_table = Get_table(table1_name);				// new table includes table 1 values
	Table table2 = Get_table(table2_name);

	// Check to see if each relation has same number of attributes
	unsigned int num_attr1, num_attr2;
	num_attr1 = new_table.Get_width();
	num_attr2 = table2.Get_width();
	if (num_attr1 != num_attr2)
		cerr << "Error during set union (different number of attributes)" << endl;

	// Check to make sure the attributes are the same in each table
	for ( unsigned int i = 0; i < num_attr1; ++i){
		if (new_table[i].Get_name() != table2[i].Get_name())
			cerr << " Error during set union (attributes do not match)" << endl;
	}

	for ( unsigned int i = 0; i < table2.Get_max_height(); ++i){	
		bool found = false;
		vector<string> row = table2.Get_row(i);								// Get row of table2 at index i
		for ( unsigned int j = 0; j < new_table.Get_max_height(); ++j)
			if (row == new_table.Get_row(j))								// Compare row of table2 at index i to each row in new_table
				found = true;												// If there are two rows that are the same set found = true
		if (!found)
			new_table.Insert_row(row);										// If row of table2 at index i is unique (found = false), add to new_table
	}
	new_table.Set_name(view_name);											//names new table
	return new_table;
}

Table Database::Set_union(string view_name, Table table1_name, Table table2_name){

	Table new_table = Table(table1_name);					// new table includes table 1 values
	Table table2 = Table(table2_name);

	// Check to see if each relation has same number of attributes
	unsigned int num_attr1, num_attr2;
	num_attr1 = new_table.Get_width();
	num_attr2 = table2.Get_width();
	if (num_attr1 != num_attr2)
		cerr << "Error during set union (different number of attributes)" << endl;

	// Check to make sure the attributes are the same in each table
	for ( unsigned int i = 0; i < num_attr1; ++i){
		if (new_table[i].Get_name() != table2[i].Get_name())
			cerr << " Error during set union (attributes do not match)" << endl;
	}

	for ( unsigned int i = 0; i < table2.Get_max_height(); ++i){
		bool found = false;
		vector<string> row = table2.Get_row(i);								// Get row of table2 at index i
		for ( unsigned int j = 0; j < new_table.Get_max_height(); ++j)
			if (row == new_table.Get_row(j))								// Compare row of table2 at index i to each row in new_table
				found = true;												// If there are two rows that are the same set found = true
		if (!found)
			new_table.Insert_row(row);										// If row of table2 at index i is unique (found = false), add to new_table
	}
	new_table.Set_name(view_name);//names new table
	return new_table;
}

Table Database::Set_difference(string view_name, string table1_name, string table2_name){

	Table table1 = Get_table(table1_name); //new table includes table 1 values
	Table table2 = Get_table(table2_name);

	// Checking to make sure Union Compatable
	// Check to see if each relation has same number of attributes
	unsigned int num_attr1, num_attr2;
	num_attr1 = table1.Get_width();
	num_attr2 = table2.Get_width();
	if (num_attr1 != num_attr2)
		cerr << "Error during set difference (different number of attributes)" << endl;

	// Check to make sure the attributes are the same in each table
	for ( unsigned int i = 0; i < num_attr1; ++i){
		if (table1[i].Get_name() != table2[i].Get_name())
			cerr << " Error during set difference (attributes do not match)" << endl;
	}
	

	Table new_table = Table(table1);			//gets copy of table1 including attribute names
	new_table.Clear_attribute_data();			//clears old data

	for ( unsigned int i = 0; i < table1.Get_max_height(); ++i){
		vector<string> row = table1.Get_row(i);							// Get row of table1 at index i
		bool found = false;
		for ( unsigned int j = 0; j < table2.Get_max_height(); ++j){
			if (row == table2.Get_row(j))								// Compare row of table1 at index i to each row in table2
				found = true;											// If there is a row in table2 = to a row[i] in table1, set found = true
		}
		if (!found)														
			new_table.Insert_row(row);									// Insert row[i] of table1 into new_table if the row is not present in table2
	}
	new_table.Set_name(view_name);										// names new table
	return new_table;
}

Table Database::Set_difference(string view_name, Table table1_name, Table table2_name){

	Table table1 = Table(table1_name); //new table includes table 1 values
	Table table2 = Table(table2_name);

	// Checking to make sure Union Compatable
	// Check to see if each relation has same number of attributes
	unsigned int num_attr1, num_attr2;
	num_attr1 = table1.Get_width();
	num_attr2 = table2.Get_width();
	if (num_attr1 != num_attr2)
		cerr << "Error during set difference (different number of attributes)" << endl;

	// Check to make sure the attributes are the same in each table
	for ( unsigned int i = 0; i < num_attr1; ++i){
		if (table1[i].Get_name() != table2[i].Get_name())
			cerr << " Error during set difference (attributes do not match)" << endl;
	}

	Table new_table = Table(table1);				//gets copy of table1 including attribute names
	new_table.Clear_attribute_data();				//clears old data

	for ( unsigned int i = 0; i < table1.Get_max_height(); ++i){
		vector<string> row = table1.Get_row(i);							// Get row of table1 at index i
		bool found = false;
		for ( unsigned int j = 0; j < table2.Get_max_height(); ++j){
			if (row == table2.Get_row(j))								// Compare row of table1 at index i to each row in table2
				found = true;											// If there is a row in table2 = to a row[i] in table1, set found = true
		}
		if (!found)
			new_table.Insert_row(row);									// Insert row[i] of table1 into new_table if the row is not present in table2
	}
	new_table.Set_name(view_name);					//names new table
	return new_table;
}

Table Database::Cross_product(string view_name, string table1_name, string table2_name){
	//set up temporary data structures
	Table my_table1 = Get_table(table1_name);
	Table my_table2 = Get_table(table2_name);
	unsigned int my_table1_height = my_table1.Get_max_height();
	unsigned int my_table2_height = my_table2.Get_max_height();
	unsigned int my_table1_width = my_table1.Get_width();
	unsigned int my_table2_width = my_table2.Get_width();
	vector<Attribute> new_attributes;
	
	//setting up new_table
	for ( unsigned int i = 0; i < my_table1_width; i++){
		new_attributes.push_back(my_table1[i]);				// get the attributes from my_table1
	}
	for ( unsigned int i = 0; i < my_table2_width; i++){
		new_attributes.push_back(my_table2[i]);				// get the attributes from my_table2
	}
	for ( unsigned int i = 0; i < new_attributes.size(); i++){
		new_attributes[i].Clear_data();						// clear the attributes' data
	}

	Table new_table;
	new_table.Set_attributes(new_attributes);				// create new_table with the new attributes
	new_table.Set_name(view_name);

	//go through each row of my_table1, concatenate them with each row of my_table2
	for ( unsigned int i = 0; i < my_table1_height; i++){
		vector<string>	row1 = my_table1.Get_row(i);
		for ( unsigned int j = 0; j < my_table2_height; ++j){
			vector<string> row2 = my_table2.Get_row(j);
			vector<string> new_row=row1;
			for ( unsigned int k = 0; k < row2.size(); ++k)
				new_row.push_back(row2[k]);
			new_table.Insert_row(new_row);
		}
	}
	return new_table;
}

Table Database::Cross_product(string view_name, Table table1_name, Table table2_name){
	//set up temporary data structures
	Table my_table1 = Table(table1_name);
	Table my_table2 = Table(table2_name);
	unsigned int my_table1_height = my_table1.Get_max_height();
	unsigned int my_table2_height = my_table2.Get_max_height();
	unsigned int my_table1_width = my_table1.Get_width();
	unsigned int my_table2_width = my_table2.Get_width();
	vector<Attribute> new_attributes;

	//setting up new_table
	for ( unsigned int i = 0; i < my_table1_width; i++){
		new_attributes.push_back(my_table1[i]);				// Get the atrrtibutes from my_table1
	}
	for ( unsigned int i = 0; i < my_table2_width; i++){
		new_attributes.push_back(my_table2[i]);				// Get the attributes from my_table2
	}
	for ( unsigned int i = 0; i < new_attributes.size(); i++){
		new_attributes[i].Clear_data();						// Clear the attributes' data
	}

	Table new_table;
	new_table.Set_attributes(new_attributes);				// create new_table with the new attributes
	new_table.Set_name(view_name);

	//go through each row of my_table1, concatenate them with each row of my_table2
	for ( unsigned int i = 0; i < my_table1_height; i++){
		vector<string>	row1 = my_table1.Get_row(i);
		for ( unsigned int j = 0; j < my_table2_height; ++j){
			vector<string> row2 = my_table2.Get_row(j);
			vector<string> new_row = row1;
			for ( unsigned int k = 0; k < row2.size(); ++k)
				new_row.push_back(row2[k]);
			new_table.Insert_row(new_row);
		}
	}
	return new_table;
}


// Command Functions

void Database::Close(string table_name){
	for ( unsigned int i = 0; i<Tables.size();++i)
		if (table_name == Tables[i].Get_name()){
			Tables.erase(Tables.begin() + i);//Deletes index i begin() returns iterator
			break;//make sure to quit iterating because we change tables vec
		}
}
void Database::Exit(){
	cout << "Closing DBMS" << endl;
	std::exit(0); 
}
Table Database::Write(string table_name){
	Table my_table=Get_table(table_name);
	ofstream out = ofstream((table_name+".db").c_str(), std::ofstream::out | std::ofstream::trunc);//trunc flag means content already in file will be deleted
	out << my_table;//Writes table to output stream

	return my_table;
}

Table Database::Write(Table table){
	bool found = false;
	for ( unsigned int i = 0; i < Tables.size(); ++i)
		if (Tables[i].Get_name() == table.Get_name()){
		Tables[i] = table;
		found = true;
		}
	if (!found)
		Tables.push_back(table);//add to database tables
	Write(table.Get_name());

	return table;
}
Table Database::Open(string table_name){
	ifstream in = ifstream((table_name + ".db").c_str());
	if (!in.is_open())
		cerr << "could not open file" << table_name + ".db"<<endl;
	else{
		Table new_table = Table();
		new_table.Read(in);
		//TODO need to implement protection against duplicate tables of same name
		if (Get_table(new_table.Get_name()).Get_name() == "DefaultTableName")
			Tables.push_back(new_table);
		else
			cout << "Table already open\n";

		return new_table;
	}
	return Table(); //error return default table
}
//For showing table in database
void Database::Show(string table_name){
	Table my_table = Get_table(table_name);
	if (my_table.Get_name() != "DefaultTableName")//check to see if get_table succeded
		my_table.Pretty_print(cout); //Pretty print, prints things nicer in the console
	else
		cout << table_name << " is not open in database\n";
}
//For showing any table
void Database::Show(Table table){
	cout << "Width: " << table.Get_width() << " Height: " << table.Get_max_height() << "\n";
	table.Pretty_print(cout);
}
Table Database::Create(string table_name,vector<string> attribute_names, vector<string> attribute_types, vector<string> keys){
	Table new_table=Table(table_name,attribute_names, attribute_types, keys);
	//TODO need to implement protection for multiple tables of the same name
	Tables.push_back(new_table);
	return new_table;
}

Table Database::Update(string table_name, vector<string> old_attributes, vector<string> new_values, string attribute_name, Token_Type comparison, string value){
	if (old_attributes.size() != new_values.size()) {
		cerr << "cant update, attribute list size does not match # of new values" << endl;
		return Table();
	}
	else{
		Table my_table = Get_table(table_name);
		Attribute comparison_attribute = my_table[attribute_name];

		vector<int> row_indicies = Compare(comparison_attribute.Get_data(), comparison, value);

		for ( unsigned int i = 0; i < row_indicies.size(); ++i)
			for ( unsigned int j = 0; j < old_attributes.size(); ++j)
				my_table[old_attributes[j]][row_indicies[i]]=new_values[j]; //old_attibutes[j] is attribute name, row_indicies[i] is the index of data to replace
		Set_table(my_table);//updates Tables vec
		return my_table;
	}
}

//having trouble with the logice in the for loop
Table Database::Update(Table &table_name, Comparison_tree *comparison, vector<pair<string, string>> new_values){
	vector<int> row_indicies = comparison->Eval_tree(table_name);
	for (unsigned int i = 0; i < row_indicies.size(); i++){
		int table_row = row_indicies[i];

		for (unsigned int j = 0; j < new_values.size(); j++) {
			table_name[j].Set_value(table_row, new_values[j].second);
		}		

	}
	Set_table(table_name);//updates Tables vec
	return table_name;
}

Table Database::Insert(string table_name, vector<string> tuple){
	Table my_table = Get_table(table_name);
	if (my_table.Get_width() != tuple.size())
		cerr << "Cant insert Tuple, size of tuple does not match table" << endl;
	else
	{
		my_table.Insert_row(tuple);
	}
	Set_table(my_table);//Updates tables vec

	return my_table;
}
Table Database::Insert(string dest_table, Table source){
	Table dest = Get_table(dest_table);
	if (dest.Get_width() != source.Get_width())
		cerr << "Can not insert from source table to dest table, table width does not match" << endl;
	else
	{
		for ( unsigned int i = 0; i < source.Get_max_height(); ++i)
			dest.Insert_row(source.Get_row(i));
	}
	Set_table(dest);//Updates tables vec
	return dest;
}

Table Database::Insert(Table &dest_name, Table source){

	if (dest_name.Get_width() != source.Get_width())
		cerr << "Can not insert from source table to dest table, table width does not match" << endl;
	else
	{
		for ( unsigned int i = 0; i < source.Get_max_height(); ++i)
			dest_name.Insert_row(source.Get_row(i));
	}
	Set_table(dest_name);//Updates tables vec
	return dest_name;
}

//Takes in a Table to add a tuple to. Tuple is in the form of a vector<string>
Table Database::Insert(Table &dest_table, vector<string> new_tuple){
	if (dest_table.Get_width() != new_tuple.size())
		cerr << "Can not insert tuple to dest table, table width does not match" << endl; //error checking
	else
			dest_table.Insert_row(new_tuple); //inserts tuple vector into table

	Set_table(dest_table);//Updates tables vec
	return dest_table;
}

//can only handle a single comparison for now, need to be able to handle Where x==a&&y==b
void Database::Delete(string table_name, string attribute_name ,Token_Type comparison, string value){//renamed remove to delete to match project requirements
	Table my_table = Get_table(table_name);
	Attribute my_attribute = my_table[attribute_name];

	vector<int> row_indicies=Compare(my_attribute.Get_data(), comparison, value);//Gets a vector of rows that match comparison

	for ( unsigned int i = 0; i < row_indicies.size(); ++i)
		my_table.Delete_row(row_indicies[i]-i);//minus i because every time you delete a row there is one less in the vector
	//ex. delete 2 4 6 becomes delete 2, delete 3, delete 4
	Set_table(my_table);//update tables vec
}

void Database::Delete(Table table_name, Attribute attribute_name, Token_Type comparison, string value){
	Table my_table = Table(table_name);
	Attribute my_attribute = attribute_name;

	vector<int> row_indicies = Compare(my_attribute.Get_data(), comparison, value);//Gets a vector of rows that match comparison

	for ( unsigned int i = 0; i < row_indicies.size(); ++i)
		my_table.Delete_row(row_indicies[i] - i);//minus i because every time you delete a row there is one less in the vector
	//ex. delete 2 4 6 becomes delete 2, delete 3, delete 4
	Set_table(my_table);//update tables vec
}

Table Database::Delete(Table &table_name, Comparison_tree *comparison){

	vector<int> row_indicies = comparison->Eval_tree(table_name);//Gets a vector of rows that match comparison

	for (unsigned int i = 0; i < row_indicies.size(); ++i)
		table_name.Delete_row(row_indicies[i] - i);//minus i because every time you delete a row there is one less in the vector
	//ex. delete 2 4 6 becomes delete 2, delete 3, delete 4
	Set_table(table_name);//update tables vec
	return table_name;
}

// Utility Functions
//no need for get_table_index(int), when you can Get_table(string)
//int Database::Get_table_index(string table_name){
//	for ( unsigned int i = 0; i < Tables.size(); ++i)
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
	for ( unsigned int i = 0; i < Tables.size(); ++i)
		if (old_name == Tables[i].Get_name()){
			Tables[i].Set_name(new_name);
			found = true;
		}
	if (!found)
		cerr << "Matching table not found, renaming therefore impossible\n";
}
Table Database::Get_table(string table_name) const{
	for ( unsigned int i = 0; i < Tables.size(); i++){
		if (Tables[i].Get_name() == table_name){
			return Tables[i];
		}
	}
	//cerr << "Table get, NOT FOUND\n";
	Table table;//IF Table not found return default
	table.Set_name(table_name);
	return table;
}
void Database::Set_table(Table& table){
	bool found = false;
	for ( unsigned int i = 0; i < Tables.size(); i++){
		if (Tables[i].Get_name() == table.Get_name()){
			Tables[i] = table;
			found = true;
		}
	}
	if (!found)
		cerr << "Table set, NOT FOUND\n";
}
//returns vector of row index where, (values[i] comparison value) evaluates to true
vector<int> Database::Compare(vector<string> values, Token_Type comparison, string value){
	vector<int> hits = vector<int>();//vector of indicies that return true for comparison
	for ( unsigned int i = 0; i < values.size(); ++i){	
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

Table Database::operator[](unsigned int i) const{
	if (i<0 || i>Tables.size()){
		cerr << "can not access Table, index out of range\n";
		return Table();
	}
	return Tables[i];
}

Table Database::operator[](string table_name) const{
	return Get_table(table_name);
}