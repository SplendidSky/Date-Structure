#include <iostream>
#include <stack>

using namespace std;

struct point {
	int i;
	int j;
	point(int i, int j) : i(i), j(j) {}
};

int BFS(bool map[][32], int N) {
	int visited[32][32];
	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 32; j++)
			visited[i][j] = 0;
	stack<point> q;
	q.push(point(0, 0));
	visited[0][0] = 1;
	while (!q.empty()) {
		point c = q.top();
		q.pop();
		if (c.i + 1 < N && map[c.i + 1][c.j] == false) {
			if (visited[c.i + 1][c.j] == 0 || visited[c.i][c.j] + 1 < visited[c.i + 1][c.j]) {
				visited[c.i + 1][c.j] = visited[c.i][c.j] + 1;
				q.push(point(c.i + 1, c.j));
			}
		}
		if (c.j + 1 < N && map[c.i][c.j + 1] == false) {
			if (visited[c.i][c.j + 1] == 0 || visited[c.i][c.j] + 1 < visited[c.i][c.j + 1]) {
				visited[c.i][c.j + 1] = visited[c.i][c.j] + 1;
				q.push(point(c.i, c.j + 1));
			}
		}
		if (c.i - 1 >= 0 && map[c.i - 1][c.j] == false) {
			if (visited[c.i - 1][c.j] == 0 || visited[c.i][c.j] + 1 < visited[c.i - 1][c.j]) {
				visited[c.i - 1][c.j] = visited[c.i][c.j] + 1;
				q.push(point(c.i - 1, c.j));
			}
		}
		if (c.j - 1 >= 0 && map[c.i][c.j - 1] == false) {
			if (visited[c.i][c.j - 1] == 0 || visited[c.i][c.j] + 1 < visited[c.i][c.j - 1]) {
				visited[c.i][c.j - 1] = visited[c.i][c.j] + 1;
				q.push(point(c.i, c.j - 1));
			}
		}
	}
	return visited[N - 1][N - 1];
}

int main() {
	int N;
	cin >> N;
	while (N != 0) {
		bool map[32][32];
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];
		cout << BFS(map, N) << endl;
		cin >> N;
	}
}