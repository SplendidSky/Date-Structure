#include <iostream>
#include <stack>

#define INFINITY 65535

using namespace std;

int Dijkstra(int adj[][210], int N, int S, int T) {
	bool found[210];
	int dis[210];
	for (int i = 0; i < N; i++) {
		found[i] = false;
		dis[i] = adj[S][i];
	}
	found[S] = true;
	dis[S] = 0;
	int v, w;
	for (int i = 0; i < N; i++) {
		int min = INFINITY;
		for (w = 0; w < N; w++) {
			if (!found[w]) {
				if (dis[w] < min) {
					v = w;
					min = dis[w];
				}
			}
		}
		found[v] = true;
		for (w = 0; w < N; w++) {
			if (!found[w])
				if (min + adj[v][w] < dis[w])
					dis[w] = min + adj[v][w];
		}
	}
	return dis[T];
}

int main() {
	do {
		int N, M;
		int adj[210][210];
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)
					adj[i][j] = 0;
				else
					adj[i][j] = INFINITY;
			}
		}
		for (int i = 0; i < M; i++) {
			int A, B, d;
			cin >> A >> B >> d;
			if (d > 0 && d < adj[A][B])
				adj[A][B] = adj[B][A] = d;
		}
		int S, T;
		cin >> S >> T;
		int d = Dijkstra(adj, N, S, T);
		if (d == INFINITY)
			cout << -1 << endl;
		else
			cout << d << endl;
	} while (!cin.eof());
}
