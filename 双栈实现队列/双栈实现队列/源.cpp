#include <stack>

using namespace std;

class Queue
{
public:
bool IsEmpty() const;
int &front();
void push(int a);
void pop();
private:
	stack<int> firstStack;
	stack<int> secondStack;
};

bool Queue::IsEmpty() const {
	return firstStack.empty() && secondStack.empty();
}

int& Queue::front() {
	if (secondStack.empty()) {
		while (!firstStack.empty()) {
			int temp = firstStack.top();
			firstStack.pop();
			secondStack.push(temp);
		}
	}
	return secondStack.top();
}

void Queue::push(int a) {
	firstStack.push(a);
}

void Queue::pop() {
	if (secondStack.empty()) {
		while (!firstStack.empty()) {
			int temp = firstStack.top();
			firstStack.pop();
			secondStack.push(temp);
		}
	}
	secondStack.pop();
}
