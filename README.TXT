CSCE 315-501
Group 1

Robert Grathwohl
Casey Brooks
Alan Achtenberg
Jacob Stone


Made and compiled in Visual Studios 2013.
Run with Visual Studios 2013 debugger using "Application" as Startup Project.














Input/Output Log:

Database Initialized

CHECK
[MAIN MENU]

1. Address Book
2. Calendar
3. Memo Pad
4. Todo List
5. Exit
* Enter app to use :3

[Memo Pad Menu]

1. Display list
2. Search
3. Edit
4. Create
5. Delete
6. Return to main menu

* Enter command: 4

[Memo Pad Create]


Creating New Memo Item
* Enter Memo: We have a meeting at 5 oclock
* Enter Memo ID: 100
* Enter Date ID: 200
*Enter the Name of the recipient: Jacob
* Enter day of the Memo Item [DD]: 10
* Enter month of the Memo Item [MM]: 10
* Enter year of the Memo Item [YYYY]: 2014
INSERT INTO memopad VALUES FROM ("We have a meeting at 5 oclock", "100", "200", "Jacob");
INSERT INTO calendar VALUES FROM ("10/10/2014", "10", "10", "2014", "200", "100", "0");

[Memo Pad Menu]

1. Display list
2. Search
3. Edit
4. Create
5. Delete
6. Return to main menu

* Enter command: 1
Displaying Memo Pad
Width:4 Height:2
-------------------------memopad-------------------------

memo		memoid		dateid		name

We have a meeting at 5 oclock		100		200		Jacob

