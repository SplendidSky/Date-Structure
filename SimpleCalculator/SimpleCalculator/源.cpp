#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

string del_spaces(const string &s) {
	string r;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ' ' && s[i] != '\n')
			r += s[i];
	}
	return r;
}

int level(const string &c) {
	if (c == ")")
		return 1;
	if (c == "(")
		return 2;
	if (c == "+" || c == "-")
		return 3;
	if (c == "*" || c == "/")
		return 4;
	return 0;
}

double str2num(string s) {
	double d;
	istringstream is(s);
	is >> d;
	return d;
}

string num2str(double n) {
	ostringstream os;
	os << n;
	return os.str();
}

stack<string> getReversePolishNotation(string s) {
	s = del_spaces(s);
	stack<string> r;
	stack<string> o;

	//预处理字符串，在正负号前面添"0"
	if (s[0] == '-' || s[0] == '+')
		s.insert(0, "0");
	for (int i = 0; i < s.length() - 1; i++) {
		if (s[i] == '(' && (s[i + 1] == '-' || s[i + 1] == '+'))
			s.insert(i + 1, "0");
	}

	for (int i = 0; i < s.length(); i++) {
		string in;

		//如果读到数字，一直读到数字的末尾
		if (s[i] >= '0' && s[i] <= '9') {
			for (int j = i; j < s.length(); j++, i++) {
				if ((s[j] < '0' || s[j] > '9') && s[j] != '.')
					break;
				in += s[j];
			}
			r.push(in);
			i--;
		}
		else if (s[i] == '(') {
			in += s[i];
			o.push(in);
		}
		else if (s[i] == ')') {
			while (o.top() != "(") {
				r.push(o.top());
				o.pop();
			}
			o.pop();
		}
		else {
			in += s[i];
			while (!o.empty() && level(o.top()) >= level(in)) {
				r.push(o.top());
				o.pop();
			}
			o.push(in);
		}
	}

	while (!o.empty()) {
		r.push(o.top());
		o.pop();
	}

	return r;
}

double calculator(string s) {
	stack<string> RPN = getReversePolishNotation(s);
	stack<string> r_RPN;
	while (!RPN.empty()) {
		r_RPN.push(RPN.top());
		RPN.pop();
	}

	stack<double> result;
	while (!r_RPN.empty()) {
		string n = r_RPN.top();
		if (n != "+" && n != "-" && n != "*" && n != "/") {
			result.push(str2num(n));
			r_RPN.pop();
		}
		else {
			double f = result.top();
			result.pop();
			double s = result.top();
			result.pop();
			if (n == "+")
				result.push(f + s);
			if (n == "-")
				result.push(s - f);
			if (n == "*")
				result.push(f * s);
			if (n == "/")
				result.push(s / f);
			r_RPN.pop();
		}
	}
	return result.top();
}


int main() {
	int N;
	string s;
	cin >> N;
	getline(cin, s);
	for (int i = 0; i < N; i++) {
		getline(cin, s);
		cout << setiosflags(ios::fixed) << setprecision(3) <<calculator(s) << endl;
	}
}
