#pragma once

enum Error_code {
	success,
	underflow,
	overflow
};

template <class List_entry>
struct Node {
	Node<List_entry>() : next(nullptr), back(nullptr) {}
	List_entry entry;
	Node<List_entry> *next;
	Node<List_entry> *back;
};

template <class List_entry>
class MyList {
public:
	MyList();
	~MyList();

	// �������캯���͸�ֵ��������أ�ע�������ǳ�����Ĳ���
	MyList(const MyList<List_entry> &copy);

	void operator =(const MyList<List_entry> &copy);

	// ���list
	void clear();

	// �ж�list�Ƿ�Ϊ��
	bool empty() const;

	// �ж�list�Ƿ�����
	bool full() const;

	// ��ȡlist��Ԫ������
	int size() const;

	// �ڵ�position��λ�ò���ֵΪentry��Ԫ�أ����positionΪ0�����������ͷ����������
	// ��position < 0 ���� position > count���򷵻�underflow
	Error_code insert(int position, const List_entry &entry);

	// ɾ����position��λ�õ�Ԫ�أ�������Ԫ�ص�ֵ������entry��
	// ��position < 0 ���� position >= count���򷵻�underflow
	Error_code remove(int position, List_entry &entry);

	// ��ȡ��position��λ�õ�Ԫ�أ�������entry��
	// ��position < 0 ���� position >= count���򷵻�underflow
	Error_code retrieve(int position, List_entry &entry) const;

	// ����position��λ�õ�Ԫ���滻Ϊentry
	// ��position < 0 ���� position >= count���򷵻�underflow
	Error_code replace(int position, const List_entry &entry);

	// ��visit��������list�����е�Ԫ��
	void traverse(void(*visit)(List_entry &));

	void display() {
		for (int i = 0; i < size(); i++) {
			List_entry entry;
			retrieve(i, entry);
			cout << entry << " ";
		}
		cout << endl;
	}
protected:
	int count;                                                          // ��¼list��Ԫ������
	mutable int curPosition;                                    // currentָ���λ�ñ��
	mutable Node<List_entry> *current;                 // currentָ��																			
	void setPosition(int position) const;                   // ����currentָ���λ�ã�ָ���position��λ��
};

template<class List_entry>
void MyList<List_entry>::setPosition(int position) const {
	int move_steps;
	bool to_next;
	if (position > curPosition) {
		move_steps = position - curPosition;
		to_next = true;
	}
	else {
		move_steps = curPosition - position;
		to_next = false;
	}

	if (to_next) {
		for (int i = 0; i < move_steps; i++) {
			current = current->next;
		}
	}
	else {
		for (int i = 0; i < move_steps; i++) {
			current = current->back;
		}
	}

	curPosition = position;
}

template<class List_entry>
inline MyList<List_entry>::MyList() {
	count = 0;
	curPosition = 0;
	current = nullptr;
}

template<class List_entry>
inline MyList<List_entry>::~MyList() {
	clear();
}

template<class List_entry>
inline MyList<List_entry>::MyList(const MyList<List_entry>& copy) {
	for (int i = 0; i < copy.size(); i++) {
		List_entry entry;
		copy.retrieve(i, entry);
		insert(i, entry);
	}
}

template<class List_entry>
inline void MyList<List_entry>::operator=(const MyList<List_entry>& copy) {
	for (int i = 0; i < copy.size(); i++) {
		List_entry entry;
		copy.retrieve(i, entry);
		insert(i, entry);
	}
}

template<class List_entry>
inline void MyList<List_entry>::clear() {
	setPosition(0);
	for (int i = 0; i < count; i++) {
		Node<List_entry> *temp = current;
		current = current->next;
		delete temp;
	}
	count = 0;
	curPosition = 0;
	current = nullptr;
}

template<class List_entry>
inline bool MyList<List_entry>::empty() const {
	return size() == 0;
}

template<class List_entry>
inline bool MyList<List_entry>::full() const {
	return false;
}

template<class List_entry>
inline int MyList<List_entry>::size() const {
	return count;
}

template<class List_entry>
inline Error_code MyList<List_entry>::insert(int position, const List_entry & entry) {
	if (position < 0 || position > count)
		return underflow;

	Node<List_entry> *new_node = new Node<List_entry>;
	new_node->entry = entry;

	if (size() == 0) {
		current = new_node;
		count++;
		return success;
	}

	if (position == 0) {
		setPosition(0);
		new_node->next = current;
		current->back = new_node;
		count++;
		curPosition++;
		return success;
	}

	setPosition(position - 1);
	new_node->back = current;
	new_node->next = current->next;
	current->next = new_node;

	count++;

	return success;
}

template<class List_entry>
inline Error_code MyList<List_entry>::remove(int position, List_entry & entry) {
	if (position < 0 || position >= count)
		return underflow;
	setPosition(position);
	Node<List_entry> *delete_node = current;
	entry = current->entry;
	if (current->next)
		current->next->back = current->back;
	if (current->back)
		current->back->next = current->next;

	count--;
	if (current->back) {
		current = current->back;
		curPosition--;
	}
	else
		current = current->next;
	delete delete_node;
	return success;
}

template<class List_entry>
inline Error_code MyList<List_entry>::retrieve(int position, List_entry & entry) const {
	if (position < 0 || position >= count)
		return underflow;
	setPosition(position);
	entry = current->entry;
	return success;
}

template<class List_entry>
inline Error_code MyList<List_entry>::replace(int position, const List_entry & entry) {
	if (position < 0 || position >= count)
		return underflow;

	setPosition(position);
	current->entry = entry;
}

template<class List_entry>
inline void MyList<List_entry>::traverse(void(*visit)(List_entry &)) {
	setPosition(0);
	for (int i = 0; i < count; i++) {
		visit(current->entry);
		current = current->next;
	}
	setPosition(0);
}

