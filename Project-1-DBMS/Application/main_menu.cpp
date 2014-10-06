#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include "main_menu.h"

using namespace std;


char check_input(char input, char low, char high){			// Used to check if input is within range of desired inputs
	bool check = false;
	char in;
	if ((input <= high) && (input >= low)){
		check = true;
	}
	while (!check){
		cout << "* Command not found, Please try again: ";
		cin >> in;
		if ((in <= high) && (in >= low)){
			input = in;
			check = true;
		}
	}
	return input;
}

void main_menu(DBParser& dbparser){

	char input, temp;

	cout << endl << "[MAIN MENU]" << endl << endl;
	cout << "1. Address Book" << endl;
	cout << "2. Calendar" << endl;
	cout << "3. Memo Pad" << endl;
	cout << "4. Todo List" << endl << endl;
	cout << "* Enter app to use: ";
	cin >> input;
	temp = check_input(input, '1', '4');

	switch (temp){
	case '1':
		Address_Book(dbparser);
		break;
	case '2':
		Calendar(dbparser);
		break;
	case '3':
		Memo_Pad(dbparser);
		break;
	case '4':
		Todo_List(dbparser);
		break;
	default:
		cerr << "Input Error!" << endl;
	}
}


// --------------------------------------------------------------
//			Converting into correct Query Formats
// --------------------------------------------------------------

string query_for_addressbook_edit(char field, string table, string name, string phone, string email, string address){
	string new_value, temp;
	switch (field){
	case '1':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";

		temp = temp + table + " " + "SET name = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + name + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET name = "new_value" WHERE(name == "name");
	break;
	case '2':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";

		temp = temp + table + " " + "SET phone = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + name + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET phone = "new_value" WHERE(name == "name");
	break;
	case '3':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";

		temp = temp + table + " " + "SET email = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + name + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET email = "new_value" WHERE(name == "name");
	break;
	case '4':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";
		temp = temp + table + " " + "SET address = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + name + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
	break;
	}
	return temp;
}
string query_for_addressbook_insert(string table, string name, string phone, string email, string address){
	string temp = "INSERT INTO ";
	temp = temp + table + " " + "VALUES FROM (";
	temp = temp + R"delim(")delim" + name + R"delim(")delim" + ", ";				// The delim lets us use quotes in our string;
	temp = temp + R"delim(")delim" + phone + R"delim(")delim" + ", ";
	temp = temp + R"delim(")delim" + email + R"delim(")delim" + ", ";
	temp = temp + R"delim(")delim" + address + R"delim(")delim" + ");";

	// OUTPUT = INSERT INTO table VALUES FROM("name", "phone", "email", "address");
	return temp;
}
string query_for_addressbook_delete(string table, string name){
	string temp = "DELETE FROM ";
	temp = temp + table + " " + "WHERE((name == ";
	temp = temp + R"delim(")delim" + name + R"delim(")delim" + "));";				// The delim lets us use quotes in our string;
	cout << temp << endl;
	return temp;
}


// --------------------------------------------------------------
//			Address Book Functions
// --------------------------------------------------------------

void retrieve_contact(DBParser& dbparser, string _name) { // not finished need to actually retrieve record from Database!!
	Table result = dbparser.execute_query("result <- select (name == \"" + _name + "\") addressbook"); // result <- select (name == "John doe") addressbook"
	cout << endl<< "Contacts matched: [" << result.Get_max_height() << "]" << endl;
	for (int i = 0; i < result.Get_max_height(); i++) {
		vector <string> row = result.Get_row(i);
		cout << endl<< "Contact[" << i+1 << "]:" << endl;
		cout << "1. Name: " << row[1]<< " " <<row[2] << endl;
		cout << "2. Phone: " << row[3] << endl;
		cout << "3. Email: " << row[4] << endl;
		cout << "4. Address: " << row[5] << endl;
	}
}



string edit_contact(DBParser& dbparser){
	string query;
	string name, phone, email, address;	
	char input, temp;
	
	cout << "*Enter name to edit: ";
	cin >> name;
	retrieve_contact(dbparser, name);

	cout << endl << "* Enter field to edit: ";
	cin >> input;
	temp = check_input(input, '1', '4');

	switch (temp){
	case '1':
		query = query_for_addressbook_edit('1', "addressbook", name, phone, email, address);
		break;
	case '2':
		query = query_for_addressbook_edit('2', "addressbook", name, phone, email, address);
		break;
	case '3':
		query = query_for_addressbook_edit('3', "addressbook", name, phone, email, address);
		break;
	case '4':
		query = query_for_addressbook_edit('4', "addressbook", name, phone, email, address);
		break;
	default:
		cerr << "Switch Error in edit_contact!" << endl;
	}
	return query;
}

string create_contact(){								// CANT HANDLE SPACES RIGHT NOW!!!!!!!!!!!!
	string query;
	string first_name, last_name, full_name;
	string phone, email, address;

	cout << endl << "Creating New Contact" << endl;
	cout << "* Enter First Name: ";
	cin >> first_name;										// CANT HANDLE SPACES RIGHT NOW!!!!!!!!!!!
	cout << "* Enter Last Name: ";
	cin >> last_name;
	full_name = first_name + last_name;
	cout << "* Enter Phone Number With No Spaces or Dashes (1234567890): ";
	cin >> phone;
	cout << "* Enter Email: ";
	cin >> email;
	cout << "* Enter Address: ";							// CANT HANDLE SPACES RIGHT NOW!!!!!!!!!!!
	cin >> address;
	
	query = query_for_addressbook_insert("addressbook", full_name, phone, email, address);
	return query;
}

string delete_contact(DBParser& dbparser){						
	bool check = false;
	string name, answer;
	string query = "";
	cout << "* Enter Name to delete: ";
	cin >> name;
	retrieve_contact(dbparser, name);
	while (!check){
		cout << "Are you sure you want to delete this record <y/n>: ";
		cin >> answer;
		if ((answer != "y") && (answer != "n")){
			cout << "Incorrect Answer Please Try Again <y/n>: ";
			cin >> answer;
		}
		else if ((answer == "y") || (answer == "n"))
			check = true;
	}
	if (answer == "y")
		query = query_for_addressbook_delete("addressbook",name);
	if (answer == "n"){
		cout << "No record Deleted" << endl;
	}
	return query;
}

// --------------------------------------------------------------
//			Calendar Functions
// --------------------------------------------------------------
string query_for_calendar_edit(char field, string table, string date, string day, string month, string year, string dateid, string memoid, string todoid){
	string new_value, temp;
	switch (field){
	case '1':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";

		temp = temp + table + " " + "SET date = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + date + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET name = "new_value" WHERE(name == "name");
		break;
	case '2':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";

		temp = temp + table + " " + "SET day = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + day + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET phone = "new_value" WHERE(name == "name");
		break;
	case '3':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";

		temp = temp + table + " " + "SET month = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + month + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET email = "new_value" WHERE(name == "name");
		break;
	case '4':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";
		temp = temp + table + " " + "SET year = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + year + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	case '5':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";
		temp = temp + table + " " + "SET dateid = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + memoid + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	case '6':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";
		temp = temp + table + " " + "SET memoid = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + dateid + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	case '7':
		cout << "*Enter new value: ";
		cin >> new_value;
		temp = "UPDATE ";
		temp = temp + table + " " + "SET todoid = ";
		temp = temp + R"delim(")delim" + new_value + R"delim(")delim" + " ";				// The delim lets us use quotes in our string;
		temp = temp + "WHERE(name == ";
		temp = temp + R"delim(")delim" + todoid + R"delim(")delim" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	}
	return temp;

}
void retrieve_calendar_date(DBParser& dbparser, string date){
	Table result = dbparser.execute_query("result <- select (name == \"" + date + "\") calendar"); // result <- select (name == "01/01/2014") calendar"
	
	cout << endl << "Dates matched: [" << result.Get_max_height() << "]" << endl;
	for (int i = 0; i < result.Get_max_height(); i++) {
		vector <string> row = result.Get_row(i);
		cout << endl << "Date[" << i + 1 << "]:" << endl;
		cout << "1. Day: " << row[1] << " " << row[2] << endl;
		cout << "2. Month: " << row[2] << endl;
		cout << "3. Year: " << row[3] << endl;
		cout << "4. DateID: " << row[4] << endl;
		cout << "5. MemoID: " << row[5] << endl;
		cout << "6. ToDoID: " << row[6] << endl;
	}
}

string edit_calendar_date(DBParser& dbparser){
	string query;
	string date, day, month, year, dateid, memoid, todoid;
	char input, temp;

	cout << "*Enter date to edit [DD/MM/YYYY]: ";
	cin >> date;
	retrieve_contact(dbparser, date);

	cout << endl << "* Enter field to edit: ";
	cin >> input;
	temp = check_input(input, '1', '7');

	switch (temp){
	case '1':
		query = query_for_calendar_edit('1', "calendar", date, day, month, year, dateid, memoid, todoid);
		break;
	case '2':
		query = query_for_calendar_edit('2', "calendar", date, day, month, year, dateid, memoid, todoid);
		break;
	case '3':
		query = query_for_calendar_edit('3', "calendar", date, day, month, year, dateid, memoid, todoid);
		break;
	case '4':
		query = query_for_calendar_edit('4', "calendar", date, day, month, year, dateid, memoid, todoid);
		break;
	case '5':
		query = query_for_calendar_edit('5', "calendar", date, day, month, year, dateid, memoid, todoid);
		break;
	case '6':
		query = query_for_calendar_edit('6', "calendar", date, day, month, year, dateid, memoid, todoid);
		break;
	case '7':
		query = query_for_calendar_edit('7', "calendar", date, day, month, year, dateid, memoid, todoid);
		break;
	default:
		cerr << "Switch Error in edit_calendar_date!" << endl;
	}
	return query;
}

// --------------------------------------------------------------
//			Main Menu Functions
// --------------------------------------------------------------
void Address_Book(DBParser& dbparser){								//FINISHED
	char input, temp;
	string query;
	string name, phone, email, address;
	string debug;

	cout << endl << "[Address Book Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Create" << endl;
	cout << "5. Delete" << endl;
	cout << "6. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;
	temp = check_input(input, '1', '6');
	Table temp_table;
	switch(temp){
		case '1':
		cout << "Displaying Address Book list " << endl;
		dbparser.execute_query("SHOW addressbook;");				// SHOULD BE CORRECT CANT FULLY TEST YET
		main_menu(dbparser);
		break;
	case '2':
		cout << "Searching in Address Book" << endl;
		cout << "* Enter Desired Name to Search For: ";				// Should be correct -robby 
		cin >> name;
		retrieve_contact(dbparser, name);
		main_menu(dbparser);
		break;
	case '3':
		cout << endl << "[Address Book Edit]" << endl << endl;
		query = edit_contact(dbparser);
		cout << endl << query << endl;
		dbparser.execute_query(query);								// SHOULD BE CORRECT CANT FULLY TEST YET
		main_menu(dbparser);
		break;
	case '4':
		cout << endl << "[Address Book Create]" << endl << endl;
		query = create_contact();
		cout << endl << query << endl;
		dbparser.execute_query(query);								//not adding any contact to the addressbook.db 
		main_menu(dbparser);
		break;
	case '5':
		cout << endl << "[Address Book Delete]" << endl << endl;
		query = delete_contact(dbparser);
		cout << endl << query << endl;
		dbparser.execute_query(query);								// SHOULD BE CORRECT CANT FULLY TEST YET
		main_menu(dbparser);
		break;
	case '6':
		main_menu(dbparser);
		break;
	default:
		cerr << "Input Error in Address book!" << endl;
	}
}

void Calendar(DBParser& dbparser){
	char input, temp;
	string name, query, date;
	cout << endl << "[Calendar Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;
	temp = check_input(input, '1', '4');
	switch (temp){
	case '1':
		cout << "Displaying Calendar list " << endl;
		dbparser.execute_query("SHOW Calendar;");
		main_menu(dbparser);
		break;
	case '2':
		cout << "Searching in Calendar" << endl;
		cout << "* Enter Desired Date to Search For: ";				
		cin >> date;
		
		main_menu(dbparser);
		break;
	case '3':
		cout << endl << "[Calendar Edit]" << endl << endl;
		query = edit_contact(dbparser);
		cout << endl << query << endl;
		dbparser.execute_query(query);								
		main_menu(dbparser);
		break;
	case '4':
		main_menu(dbparser);
		break;
	default:
		cerr << "Input Error in Calendar!" << endl;
	}
}

void Memo_Pad(DBParser& dbparser){
	char input, temp;
	cout << endl << "[Memo Pad Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Create" << endl;
	cout << "5. Delete" << endl;
	cout << "6. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;
	temp = check_input(input, '1', '6');

	switch (temp){
	case '1':
		cout << "Display list CHECK" << endl;
		break;
	case '2':
		cout << "Search CHECK" << endl;
		break;
	case '3':
		cout << "Edit CHECK" << endl;
		break;
	case '4':
		cout << "Create CHECK" << endl;
		break;
	case '5':
		cout << "Delete CHECK" << endl;
		break;
	case '6':
		main_menu(dbparser);
		break;
	default:
		cerr << "Input Error in Memo!" << endl;
	}
}

void Todo_List(DBParser& dbparser){
	char input, temp;
	cout << endl << "[Todo List Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Create" << endl;
	cout << "5. Delete" << endl;
	cout << "6. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;
	temp = check_input(input, '1', '6');

	switch (temp){
	case '1':
		cout << "Display list CHECK" << endl;
		break;
	case '2':
		cout << "Search CHECK" << endl;
		break;
	case '3':
		cout << "Edit CHECK" << endl;
		break;
	case '4':
		cout << "Create CHECK" << endl;
		break;
	case '5':
		cout << "Delete CHECK" << endl;
	case '6':
		main_menu(dbparser);
		break;
	default:
		cerr << "Input Error in Todo!" << endl;
	}
}
