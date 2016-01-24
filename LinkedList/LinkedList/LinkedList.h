#pragma once

#include <iostream>

using namespace std;

struct Node {
	int data;
	Node *next;
};

class LinkedList {
public:
	LinkedList() : size(0), head(NULL) {}
	~LinkedList();
	void insert(int position, int content);
	void deleteByPosition(int position);
	void print();
private:
	Node *head;
	int size;
};

LinkedList::~LinkedList() {
	while (1) {
		Node* temp = head;
		if (temp == NULL)
			return;
		head = head->next;
		delete temp;
	}
}

void LinkedList::insert(int position, int content) {
	if (position >= size) {
		size++;
		if (head == NULL) {
			head = new Node();
			head->data = content;
			head->next = NULL;
			return;
		}
		Node* tail = head;
		while (tail->next != NULL)
			tail = tail->next;
		Node* temp = new Node();
		temp->data = content;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
	else if (position < 0)
		return;
	else {
		size++;
		if (position == 0) {
			Node* temp = new Node();
			temp->data = content;
			temp->next = head;
			head = temp;
		}
		else {
			Node* pre_insert = head;
			for (int i = 0; i < position - 1; i++)
				pre_insert = head->next;
			Node* temp = new Node();
			temp->data = content;
			temp->next = pre_insert->next;
			pre_insert->next = temp;
		}
	}
}

void LinkedList::deleteByPosition(int position) {
	if (position >= size)
		return;
	else {
		if (position == 0) {
			Node* temp = head;
			head = head->next;
			delete temp;
			size--;
			return;
		}
		if (size == 1) {
			delete head;
			head = NULL;
			size--;
			return;
		}
		Node* pre_del = head;
		for (int i = 0; i < position - 1; i++)
			pre_del = pre_del->next;
		Node* temp = pre_del->next;
		pre_del->next = pre_del->next->next;
		delete temp;
		size--;
	}
}

void LinkedList::print() {
	for (Node* temp = head; temp != NULL; temp = temp->next) {
		cout << temp->data << '\t';
	}
	cout << endl;
}
