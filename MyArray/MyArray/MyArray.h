#pragma once

#include <iostream>

using namespace std;

class MyArray {
public:
	MyArray() : size(0) {}
	void insert(int position, int content);
	void deleteByPosition(int position);
	void print();
private:
	int contents[100];
	int size;
};

void MyArray::insert(int position, int content) {
	if (position >= size) {
		contents[size++] = content;
	}
	else if (position < 0)
		return;
	else {
		for (int i = size; i > position; i--) {
			contents[i] = contents[i - 1];
		}
		contents[position] = content;
		size++;
	}
}

void MyArray::deleteByPosition(int position) {
	if (position >= size || position < 0)
		return;
	for (int i = position; i < size - 1; i++) {
		contents[i] = contents[i + 1];
	}
	size--;
}

void MyArray::print() {
	for (int i = 0; i < size; i++) {
		cout << contents[i] << '\t';
	}
	cout << endl;
}
