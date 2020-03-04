#include "pch.h"
#include "LinkedList.h"
#include <stdlib.h>

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), s(0) {}

template <typename T>
auto LinkedList<T>::traverse(int index) -> listNode*{
	if (index < 0)
		throw "Index out of bounds";

	listNode* curr = head;
	for (int i = 0; i < index; i++) {
		if (curr == nullptr) {
			throw "Index out of bounds";
			break;
		}
		curr = curr->next;
	}

	return curr;
}

template <typename T>
void LinkedList<T>::add(T ele) {
	listNode *newNode = new listNode();
	newNode->next = nullptr;
	newNode->val = ele;
	if (tail)
		tail->next = newNode;
	tail = newNode;
	if (!head)
		head = newNode;
	s++;
}

template <typename T>
void LinkedList<T>::addAt(T ele, int index) {
	listNode *prevNode = nullptr;
	if (index != 0)
		prevNode = traverse(index - 1);

	listNode *newNode = new listNode();
	newNode->next = nullptr;
	newNode->val = ele;

	if (prevNode != nullptr) {
		newNode->next = prevNode->next;
		prevNode->next = newNode;

	}
	else {
		newNode->next = head;
		head = newNode;
	}
	if (tail == prevNode)
		tail = newNode;
	s++;
}

template <typename T>
T LinkedList<T>::get(int index) {
	return traverse(index)->val;
}

template <typename T>
bool LinkedList<T>::erase(T ele) {
	listNode *prev = nullptr, *curr = head;
	while (curr != nullptr) {
		if (curr->val == ele) {
			if (prev != nullptr) {
				prev->next = curr->next;
				if (curr == tail)
					tail = prev;
			}
			else {
				head = curr->next;
			}
			delete curr;
			s--;
			return true;
		}
		prev = curr;
		curr = curr->next;
	}
	return false;
}

template <typename T>
void LinkedList<T>::eraseAt(int index) {
	listNode *prevNode = nullptr, *toDel = head;
	if (index != 0) {
		prevNode = traverse(index - 1);
		toDel = prevNode->next;
	}
	if (toDel == nullptr)
		throw "Index out of bounds";
	prevNode->next = toDel->next;
	delete toDel;
	s--;
}

template <typename T>
void LinkedList<T>::eraseAll(T ele) {
	listNode *prev = nullptr, *curr = head;
	while (curr != nullptr) {
		if (curr->val == ele) {
			if (prev != nullptr) {
				prev->next = curr->next;
			}
			listNode *toDel = curr;
			curr = toDel->next;
			if (head == toDel) {
				head = curr;
			}
			if (tail == toDel) {
				tail = prev;
			}

			delete toDel;
			s--;
			continue;
		}
		prev = curr;
		curr = curr->next;
	}
}

template <typename T>
int LinkedList<T>::size() {
	return s;
}

template <typename T>
auto LinkedList<T>::getHead() -> listNode* {
	return head;
}

template <typename T>
auto LinkedList<T>::getTail() -> listNode* {
	return tail;
}
