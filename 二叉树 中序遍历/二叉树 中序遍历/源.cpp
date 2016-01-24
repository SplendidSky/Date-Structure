#include <stack>

using std::stack;

#ifndef NODE
#define NODE

template <class Entry>
struct Node {
	Entry entry;
	Node<Entry> *left;
	Node<Entry> *right;
};
#endif

// 二叉树的中序遍历
template <class Entry>
void inorder(Node<Entry> *root, void(*visit)(Entry &)) {
	if (!root) return;
	stack<Node<Entry> *> s;
	s.push(root);
	Node<Entry> *temp = root->left;
	while (!s.empty()) {
		while (temp) {
			s.push(temp);
			temp = temp->left;
		}
		temp = s.top();
		s.pop();
		visit(temp->entry);
		temp = temp->right;
	}
}
