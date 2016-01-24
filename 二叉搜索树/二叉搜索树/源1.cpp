#include <iostream>
using namespace std;
#ifndef NODE
#define NODE
template <class Entry>
struct Node
{
	Entry entry;
	Node<Entry> *left;
	Node<Entry> *right;
	Node(const Entry &en)
	{
		entry = en;
		left = NULL;
		right = NULL;
	}
};
#endif
// ����������Ĳ��Һ���
// ����target���ڵ�λ�ã����target���ڶ���������У��򷵻ظý���ָ��
// ���򷵻�NULL
template <class Entry>
Node<Entry>* BSTree_search(Node<Entry> *root, Entry &target) {
	while (root != NULL && root->entry != target) {
		if (root->entry < target) {
			root = root->right;
		}
		else root = root->left;
	}
	return root;
}
// ����������Ĳ��뺯��
// ��target���뵽����������У�����������Ľ����������������
// 1����������������е�Ԫ��С�ڸý���Ԫ��
// 2����������������е�Ԫ�ش��ڸý���Ԫ��
// 3��ͬһ��Ԫ���ڶ����������ֻ�����һ��
template <class Entry>
void BSTree_insert(Node<Entry> *&root, const Entry &target) {
	if (root == NULL) {
		root = new Node<Entry>(target);
		return;
	}
	if (root->entry == target) return;
	else if (root->entry < target) return BSTree_insert(root->right, target);
	else return BSTree_insert(root->left, target);
}
// �����������ɾ������
// ���target���ڶ���������У���ɾ���������򲻽����κβ���
template <class Entry>
void BSTree_remove(Node<Entry> *&subroot, const Entry &target) {
	if (subroot == NULL || subroot->entry == target)
		return remove(subroot, target);
	else if (subroot->entry < target) return BSTree_remove(subroot->right, target);
	else return BSTree_remove(subroot->left, target);
}
template <class Entry>
void remove(Node<Entry> * &root, const Entry &target) {
	if (root == NULL) return;
	Node<Entry> * to_delete = root;
	if (root->left == NULL) root = root->right;
	else if (root->right == NULL) root = root->left;
	else {
		Node<Entry> * parent = root;
		to_delete = root->left;
		while (to_delete->right != NULL) {
			parent = to_delete;
			to_delete = to_delete->right;
		}
		root->entry = to_delete->entry;
		if (parent == root) {
			root->left = to_delete->left;
		}
		else {
			parent->right = to_delete->left;
		}
	}
	delete to_delete;
}
