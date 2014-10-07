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
	cout << "4. Todo List" << endl;
	cout << "5. Exit" << endl;
	cout << "* Enter app to use: ";
	cin >> input;
	temp = check_input(input, '1', '5');

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
	case '5':
		break;
	default:
		cerr << "Input Error!" << endl;
	}
}


// --------------------------------------------------------------
//			Address Book Functions
// --------------------------------------------------------------

string query_for_addressbook_edit(char field, string table, string name,string first_name, string last_name, string phone, string email, string address){
	string new_value, first, last, full_name, temp;
	switch (field){
	case '1':
		cout << "* Enter new value for First name: ";
		cin.ignore();
		getline(cin, first);
		cout << "* Enter new value for Last name: ";
		getline(cin, last);
		full_name = first + last;

		temp = "UPDATE ";
		temp += table + " " + "SET name = ";
		temp += "\"" + full_name + "\"" + ", ";				// The delim lets us use quotes in our string;
		temp += "first = ";
		temp += "\"" + first + "\"" + ", ";
		temp += "last = ";
		temp += "\"" + last + "\"" + ", ";
		temp += "WHERE(name == ";
		temp += "\"" + name + "\"" + ");";
		// temp = UPDATE addressbook SET name = "full_name", first = "first", last = "last" WHERE(name == "name");
	break;
	case '2':
		cout << "*Enter new value for phone: ";
		cin.ignore();
		getline(cin, new_value);
		temp = "UPDATE ";
		temp += table + " " + "SET phone = ";
		temp += "\"" + new_value + "\"" + " ";
		temp += "WHERE(name == ";
		temp += "\"" + name + "\"" + ");";

	break;
	case '3':
		cout << "*Enter new value for email: ";
		cin.ignore();
		getline(cin, new_value);
		temp = "UPDATE ";
		temp += table + " " + "SET email = ";
		temp += "\"" + new_value + "\"" + " ";
		temp += "WHERE(name == ";
		temp += "\"" + name + "\"" + ");";
	break;
	case '4':
		cout << "*Enter new value for address: ";
		cin.ignore();
		getline(cin, new_value);
		temp = "UPDATE ";
		temp += table + " " + "SET address = ";
		temp += "\"" + new_value + "\"" + " ";
		temp += "WHERE(name == ";
		temp += "\"" + name + "\"" + ");";
	break;
	}
	return temp;
}
string query_for_addressbook_insert(string table, string name, string first_name, string last_name, string phone, string email, string address){
	string temp;
	temp += "INSERT INTO addressbook VALUES FROM (";
	temp += "\"" + name + "\"" + ", ";
	temp += "\"" + first_name + "\"" + ", ";
	temp += "\"" + last_name + "\"" + ", ";
	temp += "\"" + phone + "\"" + ", ";
	temp += "\"" + email + "\"" + ", ";
	temp += "\"" + address + "\"" + ");";

	// OUTPUT = INSERT INTO table VALUES FROM("name", "first_name", "last_name", "phone", "email", "address");
	return temp;
}
string query_for_addressbook_delete(string table, string name){
	string temp = "DELETE FROM ";
	temp += table + " " + "WHERE((name == ";
	temp += "\"" + name + "\"" + "));";				// The delim lets us use quotes in our string;
	cout << temp << endl;
	return temp;
}

void retrieve_contact(DBParser& dbparser, string _name) { 
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
	string full_name, first_name, last_name, phone, email, address;	
	char input, temp;
	
	cout << "* Enter first name to edit: ";
	cin >> first_name; //changed back from get line to fix \n buffer issue
	cout << "* Enter last name to edit: ";
	cin >> last_name;
	full_name = first_name + last_name;
	retrieve_contact(dbparser, full_name);

	Table result = dbparser.execute_query("result <- select (name == \"" + full_name + "\") addressbook"); // result <- select (name == "John doe") addressbook"
	for (int i = 0; i < result.Get_max_height(); i++) {
		vector <string> row = result.Get_row(i);
		full_name = row[0];
		first_name = row[1];
		last_name = row[2];
		phone = row[3];
		email = row[4];
		address = row[5];
	}
	cout << endl << "* Enter field to edit: ";
	cin >> input;
	temp = check_input(input, '1', '5');

	switch (temp){ //choosing which attribute in the Address Book table you want to edit
	case '1':
		query = query_for_addressbook_edit('1', "addressbook", full_name, first_name, last_name, phone, email, address);
		break;
	case '2':
		query = query_for_addressbook_edit('2', "addressbook", full_name, first_name, last_name, phone, email, address);
		break;
	case '3':
		query = query_for_addressbook_edit('3', "addressbook", full_name, first_name, last_name, phone, email, address);
		break;
	case '4':
		query = query_for_addressbook_edit('4', "addressbook", full_name, first_name, last_name, phone, email, address);
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
	cin.ignore();
	cout << endl << "Creating New Contact" << endl;
	cout << "* Enter First Name: ";
	getline(cin, first_name);								// CANT HANDLE SPACES RIGHT NOW!!!!!!!!!!!
	cout << "* Enter Last Name: ";
	getline(cin, last_name);
	full_name = first_name + last_name;
	cout << "* Enter Phone Number With No Spaces or Dashes (1234567890): ";
	getline(cin, phone);
	cout << "* Enter Email: ";
	getline(cin, email);
	cout << "* Enter Address: ";							// CANT HANDLE SPACES RIGHT NOW!!!!!!!!!!!
	getline(cin, address);
	
	query = query_for_addressbook_insert("addressbook", full_name, first_name, last_name, phone, email, address);
	return query;
}

string delete_contact(DBParser& dbparser){
	bool check = false;
	string first_name, last_name, name;
	char answer;
	string query = "";
	cout << "* Enter First Name to delete: ";
	cin.ignore(); //to ignore \n char left in buffer by >> operator
	getline(cin, first_name);
	cout << "* Enter Last Name to delete: ";
	getline(cin, last_name);
	name = first_name + last_name;
	retrieve_contact(dbparser, name);
	while (true){
		cout << "Are you sure you want to delete this record <y/n>: ";
		cin >> answer;

		if (answer == 'y'){
			query = query_for_addressbook_delete("addressbook", name);
			return query;
		}
		else if (answer == 'n'){
			cout << "No contact Deleted" << endl;
			return "No contact Deleted";
		}
		else {
			cout << "Incorrect Answer Please Try Again <y/n>: ";
			continue;
		}
	}
}


// --------------------------------------------------------------
//			Calendar Functions
// --------------------------------------------------------------
string query_for_calendar_edit(char field, string table, string date, string day, string month, string year, string dateid, string memoid, string todoid){
	string new_value, temp;
	switch (field){
	case '1':
		cout << "*Enter new value: ";
		getline(cin, new_value);
		temp = "UPDATE ";

		temp += table + " " + "SET date = ";
		temp += "\"" + new_value + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(date == ";
		temp += "\"" + date + "\"" + ");";
		// temp = UPDATE addressbook SET name = "new_value" WHERE(name == "name");
		break;
	case '2':
		cout << "*Enter new value: ";
		getline(cin, new_value);
		temp = "UPDATE ";

		temp += table + " " + "SET day = ";
		temp += "\"" + new_value + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(date == ";
		temp += "\"" + date + "\"" + ");";
		// temp = UPDATE addressbook SET phone = "new_value" WHERE(name == "name");
		break;
	case '3':
		cout << "*Enter new value: ";
		getline(cin, new_value);
		temp = "UPDATE ";

		temp += table + " " + "SET month = ";
		temp += "\"" + new_value + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(date == ";
		temp += "\"" + date + "\"" + ");";
		// temp = UPDATE addressbook SET email = "new_value" WHERE(name == "name");
		break;
	case '4':
		cout << "*Enter new value: ";
		getline(cin, new_value);
		temp = "UPDATE ";
		temp += table + " " + "SET year = ";
		temp += "\"" + new_value + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(date == ";
		temp += "\"" + date + "\"" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	case '5':
		cout << "*Enter new value: ";
		getline(cin, new_value);
		temp = "UPDATE ";
		temp += table + " " + "SET dateid = ";
		temp += "\"" + new_value + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(date == ";
		temp += "\"" + date + "\"" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	case '6':
		cout << "*Enter new value: ";
		getline(cin, new_value);
		temp = "UPDATE ";
		temp += table + " " + "SET memoid = ";
		temp += "\"" + new_value + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(date == ";
		temp += "\"" + date + "\"" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	case '7':
		cout << "*Enter new value: ";
		getline(cin, new_value);
		temp = "UPDATE ";
		temp += table + " " + "SET todoid = ";
		temp += "\"" + new_value + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(date == ";
		temp += "\"" + date + "\"" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	}
	return temp;

}

string query_for_calendar_edit_memopad(char field, string table, string memo, string memoid, string newmemoid, string month, string day, string year, string dateid,  string name){
	string new_value, temp;
	switch (field){

	case '2':
		temp = "UPDATE ";
		temp += table + " " + "SET memoid = ";
		temp += "\"" + newmemoid + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(memoid == ";
		temp += "\"" + memoid + "\"" + ");";
		// temp = UPDATE addressbook SET phone = "new_value" WHERE(name == "name");
		break;
	case '3':
		temp = "UPDATE ";
		temp += table + " " + "SET date = ";
		temp += "\"" + dateid + "\"" + ", ";
		temp += "month = ";
		temp += "\"" + month + "\"" + ", ";
		temp += "day = ";
		temp += "\"" + day + "\"" + ", ";
		temp += "year = ";
		temp += "\"" + year + "\"" + ", ";
		temp += "dateid = ";
		temp += "\"" + dateid + "\"" + " ";
		temp += "WHERE(memoid == ";
		temp += "\"" + memoid + "\"" + ");";
		break;
	case '4':
		temp = "UPDATE ";
		temp += table + " " + "SET name = ";
		temp += "\"" + name + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(memoid == ";
		temp += "\"" + memoid + "\"" + ");";
		// temp = UPDATE addressbook SET address = "new_value" WHERE(name == "name");
		break;
	}
	return temp;

}

string query_for_calendar_insert(string table, string day, string month, string year, string dateid, string memoid, string todoid){ // creates a query string to send to parser to isnert a tuple to calender table
	string temp = "INSERT INTO ";
	string date = day + "/" + month + "/" + year;
	temp += table + " " + "VALUES FROM (";
	temp += "\"" + date + "\"" + ", ";
	temp += "\"" + day + "\"" + ", ";
	temp += "\"" + month + "\"" + ", ";
	temp += "\"" + year + "\"" + ", ";
	temp += "\"" + dateid + "\"" + ", ";
	temp += "\"" + memoid + "\"" + ", ";
	temp += "\"" + todoid + "\"" + ");";

	// OUTPUT = INSERT INTO table VALUES FROM("date", "day", "month", "year", "dateid", "memoid", "todoid");
	return temp;
}

string  query_for_calendar_delete_memopad(string table, string memoid){ //creates a query string to send to parser for deleting a memopad calender tuple
	
	string temp = "DELETE FROM ";
	temp += table + " " + "WHERE((memoid == ";
	temp += "\"" + memoid + "\"" + "));";				// The delim lets us use quotes in our string;
	cout << temp << endl;
	return temp;


}

string query_for_calendar_delete_todolist(string table, string todoid){ // creates a query string to send to parser to delete a todolist from the calendar
	string temp = "DELETE FROM ";
	temp += table + " " + "WHERE((todoid == ";
	temp += "\"" + todoid + "\"" + "));";				// The delim lets us use quotes in our string;
	cout << temp << endl;
	return temp;

}
string query_for_calendar_edit_todolist(char field, string table, string todo, string todoid, string newtodoid, string month, string day, string year, string dateid){
	string new_value, temp;
	switch (field){

	case '2':
		temp = "UPDATE ";
		temp += table + " SET todoid = ";
		temp += "\"" + newtodoid + "\"";
		temp += " WHERE(todoid == ";
		temp += "\"" + todoid + "\"" + ");";
		// temp = UPDATE addressbook SET todoid = "new_value" WHERE(todo == "todo");
		break;
	case '3':
		temp = "UPDATE ";
		temp += table + " " + "SET date = ";
		temp += "\"" + dateid + "\"" + ", ";
		temp += "month = ";
		temp += "\"" + month + "\"" + ", ";
		temp += "day = ";
		temp += "\"" + day + "\"" + ", ";
		temp += "year = ";
		temp += "\"" + year + "\"" + ", ";
		temp += "dateid = ";
		temp += "\"" + dateid + "\"" + " ";
		//+dateid + " ";
		temp += "WHERE(todoid == ";
		temp += "\"" + todoid + "\"" + ");";
		// temp = UPDATE addressbook SET dateid = "new_value" WHERE(todo == "todo");
		break;


	}
	return temp;
}

void retrieve_calendar_date(DBParser& dbparser, string date){
	Table result = dbparser.execute_query("result <- select (date == \"" + date + "\") calendar"); // result <- select (name == "01/01/2014") calendar"
	
	cout << endl << "Dates matched: [" << result.Get_max_height() << "]" << endl;
	for (int i = 0; i < result.Get_max_height(); i++) {
		vector <string> row = result.Get_row(i);
		cout << endl << "Date[" << i + 1 << "]:" << endl;
		cout << "1. Day: " << row[1] << endl;
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
	getline(cin, date);
	retrieve_calendar_date(dbparser, date);

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
//			Memo Pad Functions
// --------------------------------------------------------------

void retrieve_memopad(DBParser& dbparser, string memoid){ //prints a memopad tuple and prints it out with indecies
	Table result = dbparser.execute_query("result <- select (memoid == \"" + memoid + "\") memopad"); 
	cout << endl << "Contacts matched: [" << result.Get_max_height() << "]" << endl;
	for (int i = 0; i < result.Get_max_height(); i++) {
		vector <string> row = result.Get_row(i);
		cout << endl << "Contact[" << i + 1 << "]:" << endl;
		cout << "1. Memo: " << row[0] << endl;
		cout << "2. MemoID: " << row[1] << endl;
		cout << "3. DateID: " << row[2] << endl;
		cout << "4. Name: " << row[3] << endl;
	}
}

string query_for_memopad_edit(char field, string table, string memo, string memoid, string new_memoid, string dateid, string name){
	string new_value, temp;
	switch (field){
	case '1':
		temp = "UPDATE ";

		temp += table + " " + "SET memo = ";
		temp += "\"" + memo + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(memoid == ";
		temp += "\"" + memoid + "\"" + ");";
		// temp = UPDATE addressbook SET memo = "new_value" WHERE(memoid == "memoid");
		break;
	case '2':

		temp = "UPDATE ";

		temp += table + " " + "SET memoid = ";
		temp += "\"" + new_memoid + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE (memoid == ";
		temp += "\"" + memoid + "\"" + ");";
		// temp = UPDATE memopad SET memoid = "new_value" WHERE(memoid == "memoid");
		break;
	case '3':

		temp = "UPDATE ";

		temp += table + " " + "SET dateid = ";
		temp += "\"" + dateid + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(memoid == ";
		temp += "\"" + memoid + "\"" + ");";
		// temp = UPDATE memopad SET dateid = "new_value" WHERE(memoid == "memoid");
		break;
	case '4':

		temp = "UPDATE ";

		temp += table + " " + "SET name = ";
		temp += "\"" + name + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(memoid == ";
		temp += "\"" + memoid + "\"" + ");";
		// temp = UPDATE memopad SET name = "new_value" WHERE(memoid == "memoid");
		break;
	}
	return temp;
}

void edit_memopad(DBParser& dbparser){
	string query;
	string memo, new_memoid, memoid, dateid, name;
	string month, day, year;
	char input, temp;

	cout << "*Enter Memo ID: ";
	cin.ignore(); // allows us to remove \n for parser to skip
	getline(cin, memoid);
	retrieve_memopad(dbparser, memoid);

	cout << endl << "* Enter field to edit: ";
	cin >> input;
	temp = check_input(input, '1', '4');

	switch (temp){
	case '1'://case to edit the memo in memopad
		cout << "*Enter new Memo: ";
		cin.ignore();
		getline(cin, memo);
		query = query_for_memopad_edit('1', "memopad", memo, memoid, new_memoid, dateid, name);
		cout << query << endl;
		dbparser.execute_query(query);
		break;
	case '2'://case to edit the memoid in memopad
		cout << "*Enter new Memo ID: ";
		cin.ignore();
		getline(cin, new_memoid);
		query = query_for_memopad_edit('2', "memopad", memo, memoid, new_memoid, dateid, name);
		cout << query << endl;
		dbparser.execute_query(query);
		query = query_for_calendar_edit_memopad('2', "calendar", memo, memoid, new_memoid, month, day, year, dateid, name);
		cout << query << endl;
		dbparser.execute_query(query);
		break;
	case '3'://case to edit the dateid in memopad
		cout << "* Enter new Month of Memo Item [MM]:";
		cin.ignore();
		getline(cin, month);
		cout << "* Enter new Day of To Do Item [DD]:";
		getline(cin, day);
		cout << "* Enter new Year of To Do Item [YYYY]:";
		getline(cin, year);
		dateid = month + "/" + day + "/" + year;

		query = query_for_memopad_edit('3', "memopad", memo, memoid, new_memoid, dateid, name);
		cout << query << endl;
		dbparser.execute_query(query);
		query = query_for_calendar_edit_memopad('3', "calendar", memo, memoid, new_memoid, month, day, year, dateid, name);
		cout << query << endl;
		dbparser.execute_query(query);
		break;
	case '4': //case to edit the name in memopad
		cout << "*Enter new name: ";
		cin.ignore();
		getline(cin, name);
		query = query_for_memopad_edit('4', "memopad", memo, memoid, new_memoid, dateid, name);
		cout << query << endl;
		dbparser.execute_query(query);
		break;
	default:
		cerr << "Switch Error in edit_memopad!" << endl;
	}
	
}

string query_for_memopad_insert(string table, string memo, string memoid, string dateid, string name){ //creates query for the insertion of memopad tuple to memopad table
	string temp = "INSERT INTO ";
	temp += table + " " + "VALUES FROM (";
	temp += "\"" + memo + "\"" + ", ";
	temp += "\"" + memoid + "\"" + ", ";
	temp += "\"" + dateid + "\"" + ", ";
	temp += "\"" + name + "\"" + ");";

	// OUTPUT = INSERT INTO table VALUES FROM("memo", "memoid", "dateid", "name');
	return temp;
}

void create_memopad(DBParser& dbparser){
	string query;
	string memo, memoid, dateid, name;
	string day, month, year;
	cout << endl << "Creating New Memo Item" << endl;
	cout << "* Enter Memo: ";
	getline(cin, memo);
	getline(cin, memo);
	cout << "* Enter Memo ID: ";
	getline(cin, memoid);
	cout << "*Enter the Name of recipient: ";
	getline(cin, name);
	cout << "* Enter month of Memo Item [MM]:";                  //Creates a new memo by reading in each line for each value
	getline(cin, month);
	cout << "* Enter day of Memo Item [DD]:";
	getline(cin, day);
	cout << "* Enter year of Memo Item [YYYY]:";
	getline(cin, year);
	dateid = month + "/" + day + "/" + year;
	query = query_for_memopad_insert("memopad", memo, memoid, dateid, name); //push memo to memopad table
	cout << query << endl;
	dbparser.execute_query(query);
	query = query_for_calendar_insert("calendar", month, day, year, dateid, memoid, "0"); //push memo to calendar table without a todoID ("0")
	cout << query << endl;
	dbparser.execute_query(query);
}

string query_for_memopad_delete(string table, string memoid){ // creates query string to delete tuple from memopad
	string temp = "DELETE FROM ";
	temp += table + " " + "WHERE((memoid == ";
	temp += "\"" + memoid + "\"" + "));";
	cout << temp << endl;
	return temp;
}

void delete_memopad(DBParser& dbparser){ //removes a memopad from the memopad and calendar table
	bool check = false;
	string memoid;
	char answer;
	string query = "";
	cout << "* Enter Memo ID to delete: ";
	cin.ignore();
	getline(cin, memoid);
	retrieve_memopad(dbparser, memoid);
	while (true){
		cout << "Are you sure you want to delete this record <y/n>:\n";
		cin >> answer;
		if (answer == 'y'){
			query = query_for_memopad_delete("memopad", memoid); // remove memopad tuple from memopad table
			dbparser.execute_query(query);
			query = query_for_calendar_delete_memopad("memopad", memoid); // remove memopad from calendar table 
			dbparser.execute_query(query);
		}
		else if (answer == 'n'){
			cout << "No Memo to be Deleted" << endl;
		}
		else {
			cout << "Incorrect Answer Please Try Again <y/n>: ";
			continue;
		}
	}	
}
// --------------------------------------------------------------
//			To Do List Functions
// --------------------------------------------------------------
void retrieve_todolist(DBParser& dbparser, string todoid){
	Table result = dbparser.execute_query("result <- select (todoid == \"" + todoid + "\") todolist"); // do we want to take in the todo or the ToDoID in order to search?
	cout << endl << "ToDos matched: [" << result.Get_max_height() << "]" << endl;
	for (int i = 0; i < result.Get_max_height(); i++) {
		vector <string> row = result.Get_row(i);
		cout << endl << "Todo[" << i + 1 << "]:" << endl;
		cout << "1. To Do: " << row[0] << endl;
		cout << "2. ToDoID: " << row[1] << endl;
		cout << "3. DateID: " << row[2] << endl;
	}
}


string query_for_todolist_edit(char field, string table, string todo, string todoid, string newtodoid, string dateid){
	string new_value, temp;
	switch (field){
	case '1':
		temp = "UPDATE ";
		temp += table + " SET todo = ";
		temp += "\"" + todo + "\"";
		temp += " WHERE(todoid == ";
		temp += "\"" + todoid + "\"" + ");";
		// temp = UPDATE addressbook SET todo = "tod0" WHERE(todoid == "todoid");
		break;
	case '2':
		temp = "UPDATE ";
		temp += table + " SET todoid = ";
		temp += "\"" + newtodoid + "\"";
		temp += " WHERE(todoid == ";
		temp += "\"" + todoid + "\"" + ");";
		// temp = UPDATE addressbook SET todoid = "todoid" WHERE(todoid == "todoid");
		break;
	case '3':
		temp = "UPDATE ";
		temp += table + " " + "SET dateid = ";
		temp += "\"" + dateid + "\"" + " ";				// The delim lets us use quotes in our string;
		temp += "WHERE(todoid == ";
		temp += "\"" + todoid + "\"" + ");";
		// temp = UPDATE addressbook SET dateid = "dateid" WHERE(todoid == "todoid");
		break;

	
	}
	return temp;

}

void edit_todolist(DBParser& dbparser){
	string query;
	string todo, todoid, newtodoid, dateid;
	string month, day, year;
	char input, temp;

	cout << "*Enter To Do List ID: ";
	cin.ignore();
	getline(cin, todoid);
	retrieve_todolist(dbparser, todoid);

	cout << endl << "* Enter field to edit: ";
	cin >> input;
	temp = check_input(input, '1', '3');

	switch (temp){
	case '1':
		cout << "*Enter new To Do: ";
		cin.ignore();
		getline(cin, todo);
		query = query_for_todolist_edit('1', "todolist", todo, todoid, newtodoid, dateid);
		cout << query << endl;
		dbparser.execute_query(query);
		break;
	case '2':
		cout << "*Enter new To Do ID value: ";
		cin.ignore();
		getline(cin, newtodoid);
		query = query_for_todolist_edit('2', "todolist", todo, todoid, newtodoid, dateid);
		cout << query << endl;
		dbparser.execute_query(query);
		query = query_for_calendar_edit_todolist('2', "calendar", todo, todoid, newtodoid, month, day, year, dateid);
		cout << query << endl;
		dbparser.execute_query(query);
		break;
	case '3':
		cout << "* Enter new Month of To Do Item [MM]:";
		cin.ignore();
		getline(cin, month);
		cout << "* Enter new Day of To Do Item [DD]:";
		getline(cin, day);
		cout << "* Enter new Year of To Do Item [YYYY]:";
		getline(cin, year);
		dateid = month + "/" + day + "/" + year;
		query = query_for_todolist_edit('3', "todolist", todo, todoid, newtodoid, dateid);
		cout << query << endl;
		dbparser.execute_query(query);
		query = query_for_calendar_edit_todolist('3', "calendar", todo, todoid, newtodoid, month, day, year, dateid);
		cout << query << endl;
		dbparser.execute_query(query);
		break;
	default:
		cerr << "Switch Error in edit_todolist!" << endl;
	}
	//return query;
}

string query_for_todolist_insert(string table, string todo, string todoid, string dateid){
	string temp = "INSERT INTO ";
	temp += table + " " + "VALUES FROM (";
	temp += "\"" + todo + "\"" + ", ";				// The delim lets us use quotes in our string;
	temp += "\"" + todoid + "\"" + ", ";
	temp += "\"" + dateid + "\"" + ");";

	// OUTPUT = INSERT INTO table VALUES FROM("todo", "todoid", "dateid");
	return temp;
}

void create_todolist(DBParser& dbparser){ //if we create a todo, how do we also push it's date to the calendar?
	string query;
	string todo, todoid, dateid;
	string day, month, year;
	cout << endl << "Creating New To Do Item" << endl;
	cout << "* Enter To Do: ";
	getline(cin, todo);
	getline(cin, todo);
	cout << "* Enter an Integer To Do ID: ";
	getline(cin, todoid);
	cout << "* Enter month of To Do Item [MM]:";
	getline(cin, month);
	cout << "* Enter day of To Do Item [DD]:";
	getline(cin, day);
	cout << "* Enter year of To Do Item [YYYY]:";
	getline(cin, year);
	dateid = month + "/" + day + "/" + year;
	query = query_for_todolist_insert("todolist", todo, todoid, dateid);//push todo to todolist table by creating the correct query string to send to parser
	cout << query << endl;
	dbparser.execute_query(query);
	query = query_for_calendar_insert("calendar", month, day, year, dateid, "0", todoid); //push todo to calendar table without memoID ("0")
	cout << query << endl;
	dbparser.execute_query(query);
}

string query_for_todolist_delete(string table, string todoid){
	string temp = "DELETE FROM ";
	temp += table + " " + "WHERE((todoid == ";
	temp += "\"" + todoid + "\"" + "));";				// The delim lets us use quotes in our string;
	cout << temp << endl;
	return temp;
}

void delete_todolist(DBParser& dbparser){
	string todoID;
	char answer;
	string query = "";
	cout << "* Enter To Do List ID to delete: ";
	cin.ignore();
	getline(cin, todoID);
	retrieve_todolist(dbparser, todoID);
	while (true){
		cout << "Are you sure you want to delete this record <y/n>: ";
		cin >> answer;

		if (answer == 'y'){
			query = query_for_todolist_delete("todolist", todoID);
			dbparser.execute_query(query);
			query = query_for_calendar_delete_todolist("calendar", todoID);
			dbparser.execute_query(query);
			break;
		}
		else if (answer == 'n'){
			cout << "No To Do Item Deleted" << endl;
			break;
		}
		else {
			cout << "Incorrect Answer Please Try Again <y/n>: ";
			continue;
		}
	}	
}

// --------------------------------------------------------------
//			Main Menu Functions
// --------------------------------------------------------------
void Address_Book(DBParser& dbparser){								//FINISHED
	char input, temp;
	string query;
	string first, last, name, phone, email, address;
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
	temp = check_input(input, '1', '6');							// check to make sure input is an option
	Table temp_table;
	switch(temp){
		case '1':
		cout << endl << "[Address Book Display]" << endl << endl;
		dbparser.execute_query("SHOW addressbook;");				// show addressbook
		Address_Book(dbparser);										// return to addressbook menu
		break;
	case '2':
		cout << endl << "[Address Book Search]" << endl << endl;
		cout << "* Enter First Name: ";		
		cin >> first;
		cout << "* Enter Last Name: ";
		cin >> last;
		name = first + last;
		retrieve_contact(dbparser, name);							// retrieve recorded of person searching for
		Address_Book(dbparser);
		break;
	case '3':
		cout << endl << "[Address Book Edit]" << endl << endl;
		query = edit_contact(dbparser);								// funciton for editing query, for editing contacts
		cout << endl << query << endl;
		dbparser.execute_query(query);								// execute the query to edit contact
		Address_Book(dbparser);
		break;
	case '4':
		cout << endl << "[Address Book Create]" << endl << endl;
		query = create_contact();									// function for create query, for creating contacts
		cout << endl << query << endl;
		dbparser.execute_query(query);								// execute the query for creating contact
		Address_Book(dbparser);
		break;
	case '5':
		cout << endl << "[Address Book Delete]" << endl << endl;
		query = delete_contact(dbparser);							// function for delete query, for delting contacts
		cout << endl << query << endl;
		dbparser.execute_query(query);								// execute the query for deleting contact
		Address_Book(dbparser);
		break;
	case '6':
		main_menu(dbparser);										// return to main menu
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
		dbparser.execute_query("SHOW calendar;");
		Calendar(dbparser);
		break;
	case '2':
		cout << "Searching in Calendar" << endl;
		cout << "* Enter Desired Date to Search For [DD/MM/YY]: ";				
		getline(cin, date);
		retrieve_calendar_date(dbparser, date);
		Calendar(dbparser);
		break;
	case '3':
		cout << endl << "[Calendar Edit]" << endl << endl;
		query = edit_calendar_date(dbparser);
		cout << endl << query << endl;
		dbparser.execute_query(query);								
		Calendar(dbparser);
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
	string query;
	string memoid, dateid;
	string debug;

	cout << endl << "[Memo Pad Menu]" << endl << endl;
	cout << "1. Display list" << endl; //completed -need to test
	cout << "2. Search" << endl; //completed - need to test
	cout << "3. Edit" << endl; //completed - need to test
	cout << "4. Create" << endl; //
	cout << "5. Delete" << endl;
	cout << "6. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;
	temp = check_input(input, '1', '6');
	Table temp_table;
	switch (temp){
	case '1':
		cout << "Displaying Memo Pad " << endl;
		dbparser.execute_query("SHOW memopad;");
		Memo_Pad(dbparser);
		break;
	case '2':
		cout << "Searching in Memo Pad" << endl;
		cout << "* Enter Desired Memo ID: ";
		cin.ignore();
		getline(cin, memoid);
		retrieve_memopad(dbparser, memoid);
		Memo_Pad(dbparser);
		break;
	case '3':
		cout << endl << "[Memo Pad Edit]" << endl << endl;
		edit_memopad(dbparser);
		Memo_Pad(dbparser);
		break;
	case '4':
		cout << endl << "[Memo Pad Create]" << endl << endl;
		create_memopad(dbparser);
		
		Memo_Pad(dbparser);
		break;
	case '5':
		cout << endl << "[Memo Pad Delete]" << endl << endl;
		delete_memopad(dbparser);
		Memo_Pad(dbparser);
		break;
	case '6':
		main_menu(dbparser);
		break;
	default:
		cerr << "Input Error in Memo Pad!" << endl;
	}
}

void Todo_List(DBParser& dbparser){
	char input, temp;
	string query;
	string todo, todoid, dateid;

	cout << endl << "[To Do List Menu]" << endl << endl;
	cout << "1. Display list" << endl; 
	cout << "2. Search" << endl; 
	cout << "3. Edit" << endl; 
	cout << "4. Create" << endl; 
	cout << "5. Delete" << endl;
	cout << "6. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;
	temp = check_input(input, '1', '6');						// check input to make sure input is an option
	
	switch (temp){
	case '1':
		cout << "Displaying To Do List " << endl;
		dbparser.execute_query("SHOW todolist;");				// show the todolist
		Todo_List(dbparser);
		break;
	case '2':
		cout << "Searching in To Do List" << endl;
		cout << "* Enter Desired To Do List ID: ";
		cin.ignore();											// ingore \n in cin buffer
		getline(cin, todoid);
		retrieve_todolist(dbparser, todoid);					// retrieves the record at the todoid
		Todo_List(dbparser);									// return to todo menu
		break;
	case '3':
		cout << endl << "[To Do List Edit]" << endl << endl;
		edit_todolist(dbparser);								// function for editing
		Todo_List(dbparser);
		break;
	case '4':
		cout << endl << "[To Do List Create]" << endl << endl;
		create_todolist(dbparser);								// functin for creating
		Todo_List(dbparser);
		break;
	case '5':
		cout << endl << "[To Do List Delete]" << endl << endl;
		delete_todolist(dbparser);								// funciton for deleting
		Todo_List(dbparser);
		break;
	case '6':
		main_menu(dbparser);									// return to main menu
		break;
	default:
		cerr << "Input Error in To Do List!" << endl;
	}
}
