#include <iostream>

using namespace std;

template <class Record>
struct Node {
	Record entry;
	Node<Record> *next;
};

template <class Record>
class Sortable_list {
public:
	Sortable_list();
	~Sortable_list();

	// �ڵ�position��λ�ò���ֵΪentry��Ԫ�أ����positionΪ0�����������ͷ���Դ�����
	// ���������У�position���� 0 <= position <= ����Ԫ������
	void insert(int position, const Record &entry);

	// �����������ݣ�ÿ����Ԫ��֮����һ���ո���������һ��Ԫ��֮��û�пո񣬲�����Ҫ����
	void print();

	// ��������й鲢������������һЩ���������������ܸĶ���ĳ�Ա����
	void merge_sort();

	void ms(Node<Record> *head, Node<Record> *tail);

	int findMid(Node<Record> *head, Node<Record> *tail);

	void merge(Node<Record> *head, Node<Record> *tail);
private:
	Node<Record> *head;                                     // ����ͷָ��
};

template<class Record>
Sortable_list<Record>::Sortable_list() {
	head = NULL;
}


template<class Record>
Sortable_list<Record>::~Sortable_list() {
	while (head) {
		Node<Record> *temp = head;
		head = head->next;
		delete temp;
	}
}

template<class Record>
void Sortable_list<Record>::insert(int position, const Record & entry) {
	if (position == 0) {
		Node<Record> *newone = new Node<Record>;
		newone->entry = entry;
		if (head == NULL) {
			head = newone;
			newone->next = NULL;
		}
		else {
			newone->next = head;
			head = newone;
		}
		return;
	}
	Node<Record> *temp = head;
	for (int i = 0; i < position - 1; i++)
		temp = temp->next;
	Node<Record> *newone = new Node<Record>;
	newone->entry = entry;
	newone->next = temp->next;
	temp->next = newone;
}

template<class Record>
void Sortable_list<Record>::print() {
	Node<Record> *temp = head;
	while (temp) {
		if (temp->next && temp->next->next == NULL)
			cout << temp->entry << endl;
		else
			cout << temp->entry << " ";
		temp = temp->next;
	}
}

template<class Record>
void Sortable_list<Record>::merge_sort() {
	ms(head, NULL);
}

template<class Record>
void Sortable_list<Record>::ms(Node<Record>* h, Node<Record>* t) {
	if (h == NULL || h->next == t) return;
	int mi = findMid(h, t);
	Node<Record> *newtail = head;
	for (int i = 0; i < mi; i++)
		newtail = newtail->next;
	ms(h, newtail);
	ms(newtail, t);
	merge(h, t);
}

template<class Record>
int Sortable_list<Record>::findMid(Node<Record> *h, Node<Record> *t) {
	if (h == NULL) return 0;
	Node<Record> *fast = h;
	int mid = 0;
	while (1) {
		fast = (fast->next == t) ? (fast->next) : (fast->next->next);
		mid++;
		if (fast == t)
			return mid;
	}
}

template<class Record>
void Sortable_list<Record>::merge(Node<Record> *h, Node<Record> *t) {
	int mi = findMid(h, t);
	Node<Record> *temp_h = h;
	Node<Record> *A_head = new Node<Record>[mi];
	Node<Record> *A = A_head;
	for (int i = 0; i < mi; i++) {
		A->entry = temp_h->entry;
		A = A->next;
		temp_h = temp_h->next;
	}
	A = A_head;
	Node<Record> *B = temp_h;
	for (int i = 0; i < mi;) {
		if (B == NULL || A->entry <= B->entry) {
			h->entry = A->entry;
			A = A->next;
			h = h->next;
			i++;
		}
		else if (B != NULL && B->entry < A->entry) {
			h->entry = B->entry;
			B = B->next;
			h = h->next;
		}
	}
}

int main() {
	Sortable_list<int> ml;
	ml.insert(0, 2);
	ml.insert(0, 5);
	ml.insert(0, 4);
	ml.insert(0, 11);
	ml.insert(0, 1);
	ml.print();
	ml.merge_sort();
	ml.print();
}