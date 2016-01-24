#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int value(char a) {
	if (a == 'a' || a == 'A') return 2;
	if (a == 'b' || a == 'B') return 4;
	if (a == 'c' || a == 'C') return 6;
	if (a == 'd' || a == 'D') return 3;
	if (a == 'e' || a == 'E') return 6;
	if (a == 'f' || a == 'F') return 9;
	if (a == 'g' || a == 'G') return 4;
	if (a == 'h' || a == 'H') return 8;
	if (a == 'i' || a == 'I') return 12;
	if (a == 'j' || a == 'J') return 5;
	if (a == 'k' || a == 'K') return 10;
	if (a == 'l' || a == 'L') return 15;
	if (a == 'm' || a == 'M') return 6;
	if (a == 'n' || a == 'N') return 12;
	if (a == 'o' || a == 'O') return 18;
	if (a == 'p' || a == 'P') return 7;
	if (a == 'q' || a == 'Q') return 14;
	if (a == 'r' || a == 'R') return 21;
	if (a == 's' || a == 'S') return 28;
	if (a == 't' || a == 'T') return 8;
	if (a == 'u' || a == 'U') return 16;
	if (a == 'v' || a == 'V') return 24;
	if (a == 'w' || a == 'W') return 9;
	if (a == 'x' || a == 'X') return 18;
	if (a == 'y' || a == 'Y') return 27;
	if (a == 'z' || a == 'Z') return 36;
}
int main() {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		int res = 0;
		char word[100];
		scanf("%s", word);
		for (int j = 0; j < strlen(word); j++)
			res += value(word[j]);
		printf("%d\n", res);
	}
}