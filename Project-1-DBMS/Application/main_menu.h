#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "Database\DBParser.h"


char check_input(char input, char low, char high);
void main_menu(DBParser& dbparser);
void Address_Book(DBParser& dbparser);
void Calendar(DBParser& dbparser);
void Memo_Pad(DBParser& dbparser);
void Todo_List(DBParser& dbparser);


#endif // MAIN_MENU_H