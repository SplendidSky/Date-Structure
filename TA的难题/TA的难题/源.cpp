#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct AC {
	int A;
	int E;
};

int main() {
	int A, B;
	cin >> A >> B;
	int M, N, T;
	vector<map<int, AC> > stus;
	for (int i = 0; i < A; i++) {
		map<int, AC> p;
		for (int j = 0; j < B; j++)
			p[j].A = p[j].E = 0;
		stus.push_back(p);
	}
	while (cin >> M >> N >> T) {
		if (T)
			stus[M - 1][N - 1].A++;
		else
			stus[M - 1][N - 1].E++;

	}
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < B; j++) {
			if (j == B - 1)
				cout << stus[i][j].A << " " << stus[i][j].E << endl;
			else
				cout << stus[i][j].A << " " << stus[i][j].E << " ";
		}
	}
}
