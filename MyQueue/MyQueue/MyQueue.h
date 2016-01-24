#include <iostream>

using namespace std;

const int maxQueue = 101;

template <class QueueEntry>
class MyQueue {
public:
	MyQueue();
	// �ж϶����Ƿ�Ϊ��
	bool empty() const;
	// ��Ӳ���
	int append(const QueueEntry &item);
	// ���Ӳ���
	int serve();
	// ��ȡ��ͷԪ��
	int retrieve(QueueEntry &item) const;
	// �ж϶����Ƿ�����
	bool full() const;
	// ��ȡ��������Ԫ�ظ���
	int size() const;
	// �����������Ԫ��
	void clear();
	// ��ȡ��ͷԪ�ز�����
	int retrieve_and_serve(QueueEntry &item);

	void print();
private:
	int front;                             // ��ͷ�±�
	int rear;                              // ��β�±�
	QueueEntry entry[100];       // ��������
};

template<class QueueEntry>
MyQueue<QueueEntry>::MyQueue() {
	front = rear = 0;
}

template<class QueueEntry>
int MyQueue<QueueEntry>::append(const QueueEntry &item) {
	if (full())
		return 2;
	entry[rear] = item;
	rear = (rear + 1 == maxQueue) ? 0 : rear + 1;
	return 0;
}

template<class QueueEntry>
inline bool MyQueue<QueueEntry>::empty() const {
	return front == rear;
}

template<class QueueEntry>
inline int MyQueue<QueueEntry>::serve() {
	if (empty())
		return 1;
	front = (front + 1 == maxQueue) ? 0 : front + 1;
	return 0;
}

template<class QueueEntry>
inline int MyQueue<QueueEntry>::retrieve(QueueEntry & item) const {
	if (empty())
		return 1;
	item = entry[front];
	return 0;
}

template<class QueueEntry>
inline bool MyQueue<QueueEntry>::full() const {
	return front == rear + 1 || (rear == maxQueue - 1 && front == 0);
}

template<class QueueEntry>
inline int MyQueue<QueueEntry>::size() const {
	int sz = 0;
	for (int temp = front; temp != rear; temp = (temp + 1 == maxQueue) ? 0 : temp + 1)
		sz++;
	return sz;
}

template<class QueueEntry>
inline void MyQueue<QueueEntry>::clear() {
	front = rear = 0;
}

template<class QueueEntry>
inline int MyQueue<QueueEntry>::retrieve_and_serve(QueueEntry & item) {
	retrieve(item);
	return serve();
}

template<class QueueEntry>
inline void MyQueue<QueueEntry>::print()
{
  for (int temp = front; temp < rear; temp++)
      cout << entry[temp] << " ";
  cout << endl;
}

