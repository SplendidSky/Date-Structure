#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool match(string s) {
	stack<char> brackets;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			brackets.push(s[i]);
		if (s[i] == ')') {
			if (!brackets.empty() && brackets.top() == '(')
				brackets.pop();
			else
				return false;
		}
		if (s[i] == ']') {
			if (!brackets.empty() && brackets.top() == '[')
				brackets.pop();
			else
				return false;
		}
		if (s[i] == '}') {
			if (!brackets.empty() && brackets.top() == '{')
				brackets.pop();
			else
				return false;
		}
	}
	if (brackets.empty())
		return true;
	return false;
}

int main() {
	int n;
	string s;
	cin >> n;
	getline(cin, s);
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		if (match(s))
			cout << "True" << endl;
		else
			cout << "False" << endl;
	}
}
