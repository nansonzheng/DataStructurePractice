#include "pch.h"
#include "LinkedList.h"

template <typename T>
class CircularList {

private:
	struct listNode {
		listNode *next;
		listNode *prev;
		T val;
	};

	listNode *head;
	listNode *tail;
	int s;

	listNode *traverse(int index) {
		listNode *node = head;
		if (node == nullptr) {
			throw "List is empty";
			return node;
		}
		int i = 0;
		while (i++ != index) {
			node = node->next;
		}
		return node;
	}

public:
	CircularList() : head(nullptr), tail(nullptr), s(0) {}
	~CircularList() {
		while (head != tail) {
			listNode *toDel = head;
			head = head->next;
			delete toDel;
		}
		delete head;
	}

	void add(T ele) {
		listNode *node = new listNode{
			head,
			tail,
			ele
		};

		if (head == nullptr) {
			head = tail = node->next = node->prev = node;
		}
		else {
			head->prev = tail->next = node;
			tail = node;
		}
		s++;
	}

	void addAt(T ele, int index) {
		listNode *old = traverse(index);
		if (old == nullptr) {
			add(ele);
			return;
		}
		
		listNode *newNode = new listNode{
			old,
			old->prev,
			ele
		};
		old->prev->next = newNode;
		old->prev = newNode;
		if (index == 0)
			head = newNode;
		s++;
	}

	void erase(T ele) {
		if (head == nullptr) {
			throw "List is empty";
			return;
		}
		listNode *toDel = head;
		while (toDel != tail && toDel->val != ele) {
			toDel = toDel->next;
		}
		if (toDel->val == ele) {
			toDel->next->prev = toDel->prev;
			toDel->prev->next = toDel->next;

			if (s == 1) {
				head = tail = nullptr;
			}
			else {
				if (toDel == head)
					head = toDel->next;
				if (toDel == tail)
					tail = toDel->prev;
			}

			delete toDel;
			s--;
		}
	}

	void eraseAt(int index) {
		if (head == nullptr) {
			throw "List is empty";
			return;
		}

		listNode *toDel = head;
		for (int i = 0; i < index; i++) {
			toDel = toDel->next;
		}
		
		toDel->next->prev = toDel->prev;
		toDel->prev->next = toDel->next;

		if (s == 1) {
			head = tail = nullptr;
		}
		else {
			if (toDel == head)
				head = toDel->next;
			if (toDel == tail)
				tail = toDel->prev;
		}

		delete toDel;
		s--;
	}

	T& get(int index) {
		return traverse(index)->val;
	}

	int size() {
		return s;
	}

	listNode *getHead() {
		return head;
	}

	listNode *getTail() {
		return tail;
	}

	class iterator {
	public:
		typedef iterator self_type;
		iterator(listNode* ptr) : _ptr(ptr) {}
		self_type operator++() { iterator i = *this;  _ptr = _ptr->next; return i; }
		self_type operator++(int) { _ptr = _ptr->next; return *this; }
		bool operator!=(const iterator& other) { return _ptr != other._ptr; }
		bool operator==(const iterator& other) { return _ptr == other._ptr; }
		T& operator*() { return _ptr->val; }
		listNode* operator->() { return _ptr; }
	private:
		listNode* _ptr;
	};

	class const_iterator {
	public:
		const_iterator(listNode *ptr) : _ptr(ptr) {}
		const_iterator operator++() { iterator i = *this; _ptr = _ptr->next; return i; }
		const_iterator operator++(int) { _ptr = _ptr->next; return *this; }
		bool operator!=(const iterator& other) { return _ptr != other._ptr; }
		bool operator==(const iterator& other) { return _ptr == other._ptr; }
		const T& operator*() { return _ptr->val; }
		const listNode* operator->() { return _ptr; }
	private:
		listNode *_ptr;
	};

	iterator begin() {
		return iterator(head);
	}
};