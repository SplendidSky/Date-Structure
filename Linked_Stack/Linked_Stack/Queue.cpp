#include "Queue.h"
#include <iostream>

using std::cout;

Queue::Queue()
{
	head = tail = nullptr;
}

Queue::~Queue()
{
	for (auto h = head; h != tail; h = h->next) {
		delete h;
	}
	head = tail = nullptr;
}

void Queue::append(Entry const & e)
{
	auto temp = new Node;
	temp->entry = e;
	temp->next = nullptr;
	if (!empty()) {
		tail->next = temp;
		tail = temp;
	}
	else {
		head = tail = temp;
	}
}

bool Queue::serve()
{
	if (!empty()) {
		auto temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
		return true;
	}
	else {
		cout << "The queue is empty !\n";
		return false;
	}
}

Entry Queue::peek() const
{
	return head->entry;
}

void Queue::display() const
{
	for (auto h = head; h != nullptr; h = h->next)
		cout << h->entry << " ";
	cout << "\n";
}

bool Queue::empty() const
{
	return head == nullptr;
}
