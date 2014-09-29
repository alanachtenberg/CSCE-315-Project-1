#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


void address_book();
void main_menu(){

	int input;

	cout << endl << "[MAIN MENU]" << endl << endl;
	cout << "1. Address Book" << endl;
	cout << "2. Calendar" << endl;
	cout << "3. Memo" << endl;
	cout << "4. Todo" << endl << endl;
	cout << "* Enter app to use: ";
	cin >> input;

	switch (input){
		case 1:
			address_book();
		break;
		case 2:
			cout << "Calender CHECK" << endl;
		break;
		case 3:
			cout << "Memo CHECK" << endl;
		break;
		case 4:
			cout << "Todo CHECK" << endl;
		break;
		default:
			cerr << "Input Error!" << endl;
	}
}

void address_book(){
	int input = 0;
	cout << endl << "[Address Book Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;

	switch (input){
		case 1:
			cout << "Display list CHECK" << endl;
			break;
		case 2:
			cout << "Search CHECK" << endl;
			break;
		case 3:
			cout << "Edit CHECK" << endl;
			break;
		case 4:
			main_menu();
			break;
		default:
			cerr << "Input Error in Address book!" << endl;
	}
}

void calendar(){
	int input = 0;
	cout << endl << "[Calendar Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;

	switch (input){
	case 1:
		cout << "Display list CHECK" << endl;
		break;
	case 2:
		cout << "Search CHECK" << endl;
		break;
	case 3:
		cout << "Edit CHECK" << endl;
		break;
	case 4:
		main_menu();
		break;
	default:
		cerr << "Input Error in Calendar!" << endl;
	}
}

void Memo(){
	int input = 0;
	cout << endl << "[Memo Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;

	switch (input){
	case 1:
		cout << "Display list CHECK" << endl;
		break;
	case 2:
		cout << "Search CHECK" << endl;
		break;
	case 3:
		cout << "Edit CHECK" << endl;
		break;
	case 4:
		main_menu();
		break;
	default:
		cerr << "Input Error in Memo!" << endl;
	}
}

void Todo(){
	int input = 0;
	cout << endl << "[Todo Menu]" << endl << endl;
	cout << "1. Display list" << endl;
	cout << "2. Search" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Return to main menu" << endl << endl;
	cout << "* Enter command: ";
	cin >> input;

	switch (input){
	case 1:
		cout << "Display list CHECK" << endl;
		break;
	case 2:
		cout << "Search CHECK" << endl;
		break;
	case 3:
		cout << "Edit CHECK" << endl;
		break;
	case 4:
		main_menu();
		break;
	default:
		cerr << "Input Error in Todo!" << endl;
	}
}


int main(){
	main_menu();
	string block;
	cout << "test" << endl;
	cin >> block;
	return 0;
}