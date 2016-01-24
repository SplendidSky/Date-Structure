#include <iostream>

using namespace std;

bool isSafe(int x, int y, int map[][8]) {
	for (int i = 0; i < 8; i++) {
		if (map[i][y] == 1)
			return false;
		if (map[x][i] == 1)
			return false;
		if (x - i >= 0 && y - i >= 0 && map[x - i][y - i] == 1)
			return false;
		if (x - i >= 0 && y + i <= 7 && map[x - i][y + i] == 1)
			return false;
		if (x + i <= 7 && y - i >= 0 && map[x + i][y - i] == 1)
			return false;
		if (x + i <= 7 && y + i <= 7 && map[x + i][y + i] == 1)
			return false;
	}
	return true;
}

void eightQueens(int x, int map2[][8]) {
	int map[8][8];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			map[i][j] = map2[i][j];

	if (x == 8) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (i < 7 && map[i][j] == 1)
					cout << j + 1 << " ";
				else if (i == 7 && map[i][j] == 1)
					cout << j + 1;
			}
		}
		cout << endl;
	}

	else {
		for (int j = 0; j < 8; j++) {
			for (int i = 0; i < 8; i++)
				map[x][i] = 0;
			if (isSafe(x, j, map)) {
				map[x][j] = 1;
				eightQueens(x + 1, map);
			}
		}
	}
}

int main() {
	int map[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			map[i][j] = 0;
		}
	}
	eightQueens(0, map);
}