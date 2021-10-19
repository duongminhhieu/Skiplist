#include "Header.h"



Column* createColumn(int value) {
	Column* temp = new Column;
	temp->value = value;
	temp->next_cell;
	return temp;
}

void createSkiplist(Skiplist& s) {
	s.head = createColumn(INT_MAX);
	s.tail = createColumn(INT_MIN);
	s.current_size = 0;
	s.MAX_LEVEL = 1;
	s.head->next_cell.push_back(s.tail);
}

bool empty(Skiplist s) {
	return s.head->next_cell[0] == s.tail;
}

Column* lowerBound(Skiplist s, int key) {
	Column* temp = s.head;
	for (int i = s.MAX_LEVEL - 1; i >= 0; i--) {
		while (temp->next_cell[i] != s.tail && temp->next_cell[i]->value < key) {
			temp = temp->next_cell[i];
		}
	}
	return temp;
}

Column* find(Skiplist s, int key) {
	// lowerBound->next maybe the value needed to find
	Column* temp = lowerBound(s, key)->next_cell[0];

	if (temp != s.tail && temp->value == key)
		return temp;

	return NULL;
}

int insert(Skiplist& s, int key) {
	if (find(s, key) != NULL)
		return -1;
	// information updating as the formula gave

	s.current_size++;
	if (int(0.2 * s.current_size) > s.MAX_LEVEL) {
		s.MAX_LEVEL++;
		s.head->next_cell.push_back(s.tail);
	}
	// chosing level as the formula gave
	int level = 0;
	for (int i = key; !(i & 1); i >>= 1)
		level++;
	level = (level + 1) % s.MAX_LEVEL;

	// create a new Column for inserting
	Column* inserted_col = createColumn(key);
	inserted_col->next_cell.resize(level + 1);
	// insert at each level lower than 'level'
	Column* temp = s.head;
	for (int i = s.MAX_LEVEL - 1; i >= 0; i--) {
		while (temp->next_cell[i] != s.tail && key > temp->next_cell[i]->value) {
			temp = temp->next_cell[i];
		}

		if (i <= level) {
			inserted_col->next_cell[i] = temp->next_cell[i];
			temp->next_cell[i] = inserted_col;
		}
	}
	return level;
}

bool erase(Skiplist& s, int key) {
	Column* erased_col = lowerBound(s, key)->next_cell[0];
	if (erased_col == s.tail || erased_col->value != key)
		return false;

	// remove conections at each level
	int level = erased_col->next_cell.size();
	Column* temp = s.head;
	for (int i = level - 1; i >= 0; i--) {
		while (temp->next_cell[i] != s.tail && key > temp->next_cell[i]->value) {
			temp = temp->next_cell[i];
		}
		temp->next_cell[i] = temp->next_cell[i]->next_cell[i];
	}
	delete erased_col;
	s.current_size--;

	return true;
}

void deleteSkiplist(Skiplist & s) { // clear the data of Skiplist s, s will be an empty Skiplist
	if (empty(s)) return;
	Column* temp = s.head;
	Column* iter = s.head;
	while (iter != s.tail) {
		temp = iter;
		iter = iter->next_cell[0];
		delete temp;
	}

	createSkiplist(s);
}

void newSkiplist(Skiplist& s) {
	deleteSkiplist(s);
	// add elements via keyboards input
	int S = 0, value = 0;
	cout << " S = "; cin >> S;
	for (int i = 0; i < S; i++) {
		printf(" x[%d] = ", i + 1);
		cin >> value;
		insert(s, value);
	}

	cout << "\nList built" << endl;
}

void printSkiplist(Skiplist s) {
	if (empty(s)) {
		cout << "List is empty" << endl;
		return;
	}

	// print elements at each level
	cout << endl;
	for (int i = s.head->next_cell.size() - 1; i > -1; i--) {
		Column* temp = s.head;
		printf("Level %d: ", i + 1);
		while (temp->next_cell[i] != s.tail) {
			cout << temp->next_cell[i]->value << "  ";
			temp = temp->next_cell[i];
		}
		cout << endl;
	}
}

void sizeofSkiplist(Skiplist s) {
	if (empty(s)) {
		cout << "List is empty" << endl;
		return;
	}

	int* count = new int[s.MAX_LEVEL + 1];
	memset(count, 0, 4 * (s.MAX_LEVEL + 1));
	// count the number of elements at each level
	// at first, count how many elements ended up at each level
	Column* temp = s.head->next_cell[0];
	while (temp != s.tail) {
		int size = temp->next_cell.size();
		count[size - 1]++;
		temp = temp->next_cell[0];
	}
	// size of level i is the total of size of the level before and count[i + 1]
	for (int i = s.MAX_LEVEL - 1; i >= 1; i--) {
		count[i - 1] += count[i];
	}

	printf("Max Level: %d\n", s.MAX_LEVEL);
	for (int i = s.MAX_LEVEL - 1; i >= 0; i--) {
		printf("size of Level %d: %d\n", i + 1, count[i]);
	}

	delete[] count;
}

int fTraverseAndLevel(Skiplist s, int key, string& traverse)
{
	traverse = "";
	Column* temp = s.head;
	for (int i = s.MAX_LEVEL - 1; i >= 0; i--) {
		while (temp->next_cell[i] != s.tail && temp->next_cell[i]->value <= key) {
			temp = temp->next_cell[i];
			traverse += to_string(temp->value) + " ";
		}
		if (temp->value == key) {
			return i;
		}
	}
	return -1;
}

void fSearchValue(Skiplist s, int key)
{
	string traverse = "";
	int flag = fTraverseAndLevel(s, key, traverse);
	if (flag != -1)
	{
		cout << "Level of " << key << ": " << flag << endl;
		cout << "Traverse path: " << traverse << endl;
	}
	else
		cout << "val not found" << endl;
}

void fInsertValue(Skiplist& s, int key)
{
	int flag = insert(s, key);
	if (flag != -1) 
	{
		cout << key << "val inserted with level: " << flag << endl;
		return;
	}
	cout << key << "val already inserted" << endl;
}

void fRemoveValue(Skiplist& s, int key)
{
	if (!erase(s, key)) {
		cout << key << "val not found " << endl;
		return;
	}
	cout << key << "val removed" << endl;
}
