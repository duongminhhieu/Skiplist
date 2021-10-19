#pragma once
#include <iostream>
#include <vector>
#include<string>
using namespace std;

struct Column {
	int value;
	vector<Column*> next_cell;
};

struct Skiplist {
	int MAX_LEVEL;
	int current_size;
	Column* head;
	Column* tail;
};


Column* createColumn(int key); // initialize a Column
void createSkiplist(Skiplist& s); // initialize a Skiplist 
bool empty(Skiplist s); // check if Skiplist is empty
Column* lowerBound(Skiplist s, int key); // find a column that has the bigest value but lower than key.

// Methods
Column* find(Skiplist s, int key);
int insert(Skiplist& s, int key);
bool erase(Skiplist& s, int key); // return true if it is able to delete key

void deleteSkiplist(Skiplist& s); // clear data
void newSkiplist(Skiplist& s); // Task 1 
void printSkiplist(Skiplist s); // Task 2
void sizeofSkiplist(Skiplist s);// Task 3


int fTraverseAndLevel(Skiplist s, int key, string& traverse);//find traverse path and lv of value
void fSearchValue(Skiplist s, int key);// Task 4
void fInsertValue(Skiplist& s, int key);// Task 5
void fRemoveValue(Skiplist& s, int key);// Task 6