#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include "main_menu.h"
//#include "Database\DBParser.h"

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

void main_menu(DBParser dbparser){

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
		cout << "Calender CHECK" << endl;
		break;
	case '3':
		cout << "Memo Pad CHECK" << endl;
		break;
	case '4':
		cout << "Todo List CHECK" << endl;
		break;
	default:
		cerr << "Input Error!" << endl;
	}
}

void Address_Book(DBParser dbparser){
	char input, temp;
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

	switch (temp){
		case '1':
		cout << "Display list CHECK" << endl;
		dbparser.execute_query("SHOW addressbook");
		break;
	case '2':
		cout << "Search CHECK" << endl;
		break;
	case '3':
		cout << "Edit CHECK" << endl;
		break;
	case '4':
		cout << "Create CHECK" << endl; 
		dbparser.execute_query("INSERT INTO addressbook VALUES FROM("Jacob Stone", "512-466-4467", "jacob.stone56@tamu.edu", "1713 Laura");");
		break;
	case '5':
		cout << "Delete CHECK" << endl;
		break;
	case '6':
		main_menu(dbparser);
		break;
	default:
		cerr << "Input Error in Address book!" << endl;
	}
}

void Calendar(DBParser dbparser){
	char input, temp;
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
		cout << "Display list CHECK" << endl;
		break;
	case '2':
		cout << "Search CHECK" << endl;
		break;
	case '3':
		cout << "Edit CHECK" << endl;
		break;
	case '4':
		main_menu(dbparser);
		break;
	default:
		cerr << "Input Error in Calendar!" << endl;
	}
}

void Memo_Pad(DBParser dbparser){
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

void Todo_List(DBParser dbparser){
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
