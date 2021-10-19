#include "Header.h"

using namespace std;

void printMenu() {

	cout << endl << "\t ========================== MENU ==========================\n";
	cout << endl << "\t\t1. Create new Skiplist";
	cout << endl << "\t\t2. Print Skiplist ";
	cout << endl << "\t\t3. Size ";
	cout << endl << "\t\t4. Search value ";
	cout << endl << "\t\t5. Insert value ";
	cout << endl << "\t\t6. Remove value ";

	cout << endl << "\t\t0. Exit";
	cout << endl << "\t\ Enter your choice: ";

	return;
}

void loadMenu() {

	int choice;
	Skiplist s;
	createSkiplist(s);
	int key;

	do
	{
		printMenu();
		cin >> choice;

		switch (choice)
		{

		case 1:
			system("cls");
			cout << endl << "\t\t=============== Task 1: new S x1 x2 ... xS =============== \n";
			newSkiplist(s);
			break;

		case 2:
			system("cls");
			cout << endl << "\t\t=============== Task 2: Print ============================ \n";
			printSkiplist(s);
			break;

		case 3:
			system("cls");
			cout << endl << "\t\t=============== Task 3: Size ============================= \n";
			sizeofSkiplist(s);
			break;

		case 4:
			system("cls");
			cout << endl << "\t\t=============== Task 4: Search val ======================= \n";
			cout << " Enter key: ";
			cin >> key;
			fSearchValue(s, key);
			break;

		case 5:
			system("cls");
			cout << endl << "\t\t=============== Task 5: Insert val ======================= \n";
			cout << " Enter key: ";
			cin >> key;
			fInsertValue(s, key);
			printSkiplist(s);
			break;

		case 6:
			system("cls");
			cout << endl << "\t\t=============== Task 6: Remove val ======================= \n";
			cout << " Enter key: ";
			cin >> key;
			fRemoveValue(s, key);
			printSkiplist(s);
			break;
		default:
			break;
		}

	} while (choice > 0);


}

int main()
{
	loadMenu();

	cout << "\n\n";
	system("pause");
	return 0;
}