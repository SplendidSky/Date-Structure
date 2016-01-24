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
	判断栈是否为空，若为空则返回true，非空则返回false
	*/
	bool empty() const;
	int size() const;
	/*
	出栈操作，若正常出栈则返回success，若栈内无元素则返回underflow
	*/
	ErrorCode pop();
	/*
	获取栈顶元素，若正常获取到栈顶元素则返回success，若栈内无元素则返回underflow
	元素内容保存在引用参数item中
	*/
	ErrorCode top(StackEntry &item) const;
	/*
	入栈操作，若正常入栈则返回success，若入栈失败则返回overflow
	*/
	ErrorCode push(const StackEntry &item);
	/*
	清空栈
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

