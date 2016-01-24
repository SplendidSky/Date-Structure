#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct person {
	int id;
	int water;
	person *left;
	person *right;
	person(int id, int water) : id(id), water(water) { left = NULL; right = NULL; }
};

void insert(person *&root, person* p) {
	if (root == NULL) root = p;
	else {
		if (root->water <= p->water) insert(root->right, p);
		else insert(root->left, p);
	}
}

void inorder(person *root, vector<person> &r) {
	if (root == NULL) return;
	inorder(root->left, r);
	r.push_back(*root);
	inorder(root->right, r);
}

int main() {
	int n;
	cin >> n;
	person *root = NULL;
	for (int i = 0; i < n; i++) {
		int water;
		cin >> water;
		person *newone = new person(i + 1, water);
		insert(root, newone);
	}
	vector<person> people;
	inorder(root, people);
	double t = 0;
	for (int i = 0; i < people.size(); i++) {
		if (i == people.size() - 1)
			cout << people[i].id << endl;
		else
			cout << people[i].id << " ";
		for (int j = 0; j < i; j++)
			t += people[j].water;
	}
	cout << setiosflags(ios::fixed);
	cout << setprecision(2) << t / people.size() << endl;
}
