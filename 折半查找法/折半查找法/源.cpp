#include <vector>
#include <iostream>
using namespace std;

template <typename T>
int binarySearch(const vector<T> table, int bot, int top, const T &x) {
	while (bot <= top) {
		int mid = (bot + top) >> 1;
		if (x < table[mid]) top = mid - 1;
		else if (table[mid] < x) bot = mid + 1;
		else {
			T t = table[mid];
			while (table[++mid] == t);
			return mid - 1;
		}
	}
	return -1;
}

int main() {
	int a[] = { 0,1, 1,3,3,3,6 };

	vector<int> v(a, a + 7);

	cout << binarySearch(v, 0, v.size() - 1, 3);  // Êä³ö5

	cout << binarySearch(v, 0, v.size() - 1, 7);  //Êä³ö-1


}