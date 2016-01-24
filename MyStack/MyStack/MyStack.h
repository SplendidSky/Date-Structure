#pragma once
enum ErrorCode {
	success,
	underflow,
	overflow
};

const int maxStack = 100;

template <class StackEntry>
class MyStack {
public:
	MyStack() : size(0) {};
	bool empty() const;
	ErrorCode pop();
	ErrorCode top(StackEntry &item) const;
	ErrorCode push(const StackEntry &item);
private:
	int size;
	StackEntry entry[maxStack];
};

template<class StackEntry>
inline bool MyStack<StackEntry>::empty() const {
	return size == 0;
}

template<class StackEntry>
inline ErrorCode MyStack<StackEntry>::pop() {
	if (size == 0)
		return ErrorCode::underflow;
	size--;
	return ErrorCode::success;
}

template<class StackEntry>
inline ErrorCode MyStack<StackEntry>::top(StackEntry & item) const {
	if (size == 0)
		return ErrorCode::underflow;
	item = entry[size - 1];
	return ErrorCode::success;
}

template<class StackEntry>
inline ErrorCode MyStack<StackEntry>::push(const StackEntry &item) {
	if (size == maxStack)
		return ErrorCode::overflow;
	entry[size++] = item;
	return ErrorCode::success;
}