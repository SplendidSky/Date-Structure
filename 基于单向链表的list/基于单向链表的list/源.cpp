enum Error_code {
	success,
	underflow,
	overflow
};

template <class List_entry>
struct Node {
	List_entry entry;
	Node<List_entry> *next;
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
protected:
	int count;                                                         // ��¼list��Ԫ������
	Node<List_entry> *head;                                         // ����ͷָ��
	mutable int curPosition;                                   // currentָ���λ�ñ��
	mutable Node<List_entry> *current;                 // currentָ�� 
	// ����currentָ���λ�ã�ָ���position��λ��
	void setPosition(int position) const;
};

template<class List_entry>
MyList<List_entry>::MyList() {
	count = 0;
	head = NULL;
	curPosition = 0;
	current = NULL;
}

template<class List_entry>
MyList<List_entry>::~MyList() {
	clear();
}

template<class List_entry>
MyList<List_entry>::MyList(const MyList<List_entry>& copy) {
	Node<List_entry> *head = new Node<List_entry>;
	for (int i = 0; i < copy.size(); i++) {
		List_entry entry;
		copy.retrieve(i, entry);
		insert(i, entry);
	}
}

template<class List_entry>
MyList<List_entry>::operator=(const MyList<List_entry> &copy) {
	
}

template<class List_entry>
void MyList<List_entry>::clear() {
	while (head != NULL) {
		Node<List_entry> *temp = head;
		head = head->next;
		delete temp;
	}
	count = 0;
	curPosition = 0;
	current = NULL;
}

template<class List_entry>
bool MyList<List_entry>::empty() const {
	return count == 0;
}

template<class List_entry>
bool MyList<List_entry>::full() const {
	return false;
}

template<class List_entry>
int MyList<List_entry>::size() const {
	return count;
}

template<class List_entry>
Error_code MyList<List_entry>::insert(int position, const List_entry & entry) {
	if (position < 0 || position > count)
		return underflow;
	Node<List_entry> *new_node = new Node<List_entry>;
	new_node->entry = entry;
	if (position == 0) {
		new_node->next = head;
	}
	else {
		Node<List_entry> *temp = head;
		for (int i = 0; i < position - 1; i++)
			temp = temp->next;
		new_node->next = temp->next;
		temp->next = new_node;
	}
	count++;
	return success;
}

template<class List_entry>
Error_code MyList<List_entry>::remove(int position, List_entry & entry) {
	if (position < 0 || position >= count)
		return underflow;
	Node<List_entry> *temp = head;
	if (position == 0) {
		entry = temp->entry;
		head = head->next;
		delete temp;
	}
	else {
		for (int i = 0; i < position - 1; i++)
			temp = temp->next;
		Node<List_entry> *delete_node = temp->next;
		temp->next = temp->next->next;
		entry = delete_node->entry;
		delete delete_node;
	}
	count--;
	return success;
}

template<class List_entry>
Error_code MyList<List_entry>::retrieve(int position, List_entry & entry) const {
	if (position < 0 || position >= count)
		return underflow;
	Node<List_entry> *temp = head;
	for (int i = 0; i < position; i++)
		temp = temp->next;
	entry = temp->entry;
}

template<class List_entry>
Error_code MyList<List_entry>::replace(int position, const List_entry & entry) {
	if (position < 0 || position >= count)
		return underflow;
	Node<List_entry> *temp = head;
	for (int i = 0; i < position; i++)
		temp = temp->next;
	temp->entry = entry;
	return success;
}

template<class List_entry>
void MyList<List_entry>::traverse(void(*visit)(List_entry &)) {
	Node<List_entry> *temp = head;
	for (int i = 0; i < count; i++, temp = temp->next)
		visit(*temp);
}

template<class List_entry>
void MyList<List_entry>::setPosition(int position) const {
	current = head;
	for (int i = 0; i < position; i++)
		current = current->next;
}

