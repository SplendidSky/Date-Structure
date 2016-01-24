#include <iostream>
#include <string>

using namespace std;

void getNext(string T, int next[]) {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < T.length() - 1) {
		if (-1 == j || T[i] == T[j]) {
			//重复时提高效率
			if (T[i] == T[i + 1] && i > 1) {
				i++;
				next[i] = j;
			}
			else {
				j++;
				i++;
				next[i] = j;
			}
		}
		else
			j = next[j];
	}
}

int KMP(string S, string T) {
	int i = 0, j = 0, next[100];
	getNext(T, next);
	while (i < S.length()) {
		if (-1 == j || S[i] == T[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];   //消除了主串的回溯
		}
		if (j == T.length())
			return i - T.length();
	}
	return -1;
}

int main() {
	string s = "aaaa";
	string t = "a";
	cout << KMP(s, t) << endl;
}