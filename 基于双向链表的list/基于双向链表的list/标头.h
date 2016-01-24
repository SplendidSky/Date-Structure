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

	// 拷贝构造函数和赋值运算符重载，注意深拷贝与浅拷贝的差异
	MyList(const MyList<List_entry> &copy);

	void operator =(const MyList<List_entry> &copy);

	// 清空list
	void clear();

	// 判断list是否为空
	bool empty() const;

	// 判断list是否已满
	bool full() const;

	// 获取list的元素数量
	int size() const;

	// 在第position个位置插入值为entry的元素，如果position为0则插入在链表头，依次类推
	// 若position < 0 或者 position > count，则返回underflow
	Error_code insert(int position, const List_entry &entry);

	// 删除第position个位置的元素，并将该元素的值保存在entry中
	// 若position < 0 或者 position >= count，则返回underflow
	Error_code remove(int position, List_entry &entry);

	// 获取第position个位置的元素，保存在entry中
	// 若position < 0 或者 position >= count，则返回underflow
	Error_code retrieve(int position, List_entry &entry) const;

	// 将第position个位置的元素替换为entry
	// 若position < 0 或者 position >= count，则返回underflow
	Error_code replace(int position, const List_entry &entry);

	// 用visit函数遍历list内所有的元素
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
	int count;                                                          // 记录list内元素数量
	mutable int curPosition;                                    // current指针的位置编号
	mutable Node<List_entry> *current;                 // current指针																			
	void setPosition(int position) const;                   // 设置current指针的位置，指向第position个位置
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

