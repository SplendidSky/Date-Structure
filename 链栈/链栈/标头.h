#pragma once
enum ErrorCode {
	success,
	underflow,
	overflow
};

template <class StackEntry>

struct Node {
	StackEntry data;
	Node *next;
};

template <class StackEntry>
class MyStack {
public:
	MyStack();
	/*
	�ж�ջ�Ƿ�Ϊ�գ���Ϊ���򷵻�true���ǿ��򷵻�false
	*/
	bool empty() const;
	int size() const;
	/*
	��ջ��������������ջ�򷵻�success����ջ����Ԫ���򷵻�underflow
	*/
	ErrorCode pop();
	/*
	��ȡջ��Ԫ�أ���������ȡ��ջ��Ԫ���򷵻�success����ջ����Ԫ���򷵻�underflow
	Ԫ�����ݱ��������ò���item��
	*/
	ErrorCode top(StackEntry &item) const;
	/*
	��ջ��������������ջ�򷵻�success������ջʧ���򷵻�overflow
	*/
	ErrorCode push(const StackEntry &item);
	/*
	���ջ
	*/
	void clear();
private:
	Node<StackEntry> *pTop;
};

template<class StackEntry>
MyStack<StackEntry>::MyStack() {
	pTop = 0;
}

template<class StackEntry>
inline bool MyStack<StackEntry>::empty() const {
	return size() == 0;
}

template<class StackEntry>
inline int MyStack<StackEntry>::size() const {
	int sz = 0;
	Node<StackEntry> *top = pTop;
	while (top != 0) {
		top = top->next;
		sz++;
	}
	return sz;
}

template<class StackEntry>
inline ErrorCode MyStack<StackEntry>::pop()
{
	if (empty())
		return underflow;
	Node<StackEntry> *temp = pTop;
	pTop = pTop->next;
	delete temp;
	return success;
}

template<class StackEntry>
inline ErrorCode MyStack<StackEntry>::top(StackEntry & item) const
{
	if (empty())
		return underflow;
	item = pTop->data;
	return success;
}

template<class StackEntry>
inline ErrorCode MyStack<StackEntry>::push(const StackEntry & item)
{
	Node<StackEntry> *n = new Node<StackEntry>;
	n->next = pTop;
	n->data = item;
	pTop = n;
	return success;
}

template<class StackEntry>
inline void MyStack<StackEntry>::clear()
{
	while (pTop != 0) {
		Node<StackEntry> *temp = pTop;
		pTop = pTop->next;
		delete temp;
	}
}

