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
	// 判断队列是否为空
	bool empty() const;
	// 入队操作
	ErrorCode append(const QueueEntry &item);
	// 出队操作
	ErrorCode serve();
	// 获取队头元素
	ErrorCode retrieve(QueueEntry &item) const;
	// 获取队列已有元素个数
	int size() const;
	// 清除队列所有元素
	void clear();
	// 获取队头元素并出队
	ErrorCode retrieve_and_serve(QueueEntry &item);

private:
	Node<QueueEntry> *front;                           // 队头指针
	Node<QueueEntry> *rear;                             // 队尾指针
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
