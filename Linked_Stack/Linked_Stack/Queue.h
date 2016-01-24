#pragma once

#define Entry int

struct Node {
	Node *next;
	Entry entry;
};
class Queue {
public:
	Queue();
	~Queue();
	void append(Entry const &e);
	bool serve();
	bool empty() const;
	Entry peek() const;
	void display() const;
private:
	Node *head;
	Node *tail;
};

