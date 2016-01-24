#pragma once
enum ErrorCode {
	success,
	underflow,
	overflow
};



template <class QueueEntry>
struct Node {
	QueueEntry data;
	Node<QueueEntry> *next;
};

template <class QueueEntry>
class MyQueue {
public:
	MyQueue();
	// �ж϶����Ƿ�Ϊ��
	bool empty() const;
	// ��Ӳ���
	ErrorCode append(const QueueEntry &item);
	// ���Ӳ���
	ErrorCode serve();
	// ��ȡ��ͷԪ��
	ErrorCode retrieve(QueueEntry &item) const;
	// ��ȡ��������Ԫ�ظ���
	int size() const;
	// �����������Ԫ��
	void clear();
	// ��ȡ��ͷԪ�ز�����
	ErrorCode retrieve_and_serve(QueueEntry &item);

private:
	Node<QueueEntry> *front;                           // ��ͷָ��
	Node<QueueEntry> *rear;                             // ��βָ��
};

template<class QueueEntry>
inline MyQueue<QueueEntry>::MyQueue() {
	front = rear = 0;
}

template<class QueueEntry>
inline bool MyQueue<QueueEntry>::empty() const {
	return size() == 0;
}

template<class QueueEntry>
inline ErrorCode MyQueue<QueueEntry>::append(const QueueEntry & item) {
	if (size() == 0) {
		front = new Node<QueueEntry>;
		front->data = item;
		front->next = 0;
		rear = front;
	}
	else {
		Node<QueueEntry> *temp = new Node<QueueEntry>;
		temp->data = item;
		temp->next = 0;
		rear->next = temp;
		rear = temp;
	}
	return success;
}

template<class QueueEntry>
inline ErrorCode MyQueue<QueueEntry>::serve() {
	if (empty())
		return underflow;
	if (size() == 1)
		clear();
	else {
		Node<QueueEntry> *temp = front;
		front = front->next;
		delete temp;
	}
	return success;
}

template<class QueueEntry>
inline ErrorCode MyQueue<QueueEntry>::retrieve(QueueEntry & item) const {
	if (empty())
		return underflow;
	item = front->data;
	return success;
}

template<class QueueEntry>
inline int MyQueue<QueueEntry>::size() const {
	int sz = 0;
	Node<QueueEntry> *f = front;
	while (f != 0) {
		f = f->next;
		sz++;
	}
	return sz;
}

template<class QueueEntry>
inline void MyQueue<QueueEntry>::clear() {
	while (front != 0) {
		Node<QueueEntry> *temp = front;
		front = front->next;
		delete temp;
	}
	rear = 0;
}

template<class QueueEntry>
inline ErrorCode MyQueue<QueueEntry>::retrieve_and_serve(QueueEntry & item) {
	retrieve(item);
	return serve();
}
