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



// 二叉树的先序遍历

template <class Entry>
void preorder(Node<Entry> *root, void(*visit)(Entry &)) {
	if (!root) return;
	stack<Node<Entry> *> s;
	s.push(root);
	while (!s.empty()) {
		Node<Entry> *temp = s.top();
		visit(temp->entry);
		s.pop();
		if (temp->right)
			s.push(temp->right);
		if (temp->left)
			s.push(temp->left);
	}
}
