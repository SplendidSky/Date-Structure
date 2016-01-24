#include <iostream>

using namespace std;

int findMax(int F[], int N) {
	int max = F[0];
	for (int i = 1; i < N; i++) {
		if (max < F[i])
			max = F[i];
	}
	return max;
}

int bs(int H[], int h, int lo, int hi) {
	if (lo >= hi) return 0;
	int mi = (lo + hi) >> 1;
	if (H[mi] < h) return bs(H, h, mi + 1, hi);
	else if (h < H[mi]) return bs(H, h, lo, mi);
	else return mi;
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int M, N, F[22];
		cin >> M >> N;
		int *H = new int[N];
		for (int i = 0; i < M; i++)
			cin >> F[i];
		for (int i = 0; i < N; i++)
			cin >> H[i];
		cout << 50 * bs(H, findMax(F, M), 0, N) << endl;
		delete[] H;
	}
}
