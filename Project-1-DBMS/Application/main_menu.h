#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "Database\DBParser.h"


char check_input(char input, char low, char high);
void main_menu(DBParser& dbparser);
void Address_Book(DBParser& dbparser);
void Calendar(DBParser& dbparser);
void Memo_Pad(DBParser& dbparser);
void Todo_List(DBParser& dbparser);

// Functions for Converting into correct Query Formats
string query_for_addressbook_edit(char field, string table, string name, string first, string last, string phone, string email, string address);
string query_for_addressbook_delete(string table, string name);
string query_for_addressbook_insert(string table, string name, string phone, string email, string address);

#endif // MAIN_MENU_H