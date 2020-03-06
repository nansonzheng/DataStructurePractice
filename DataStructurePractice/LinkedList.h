#pragma once
#ifndef LLIST_H
#define LLIST_H
#include "pch.h"

template <typename T>
class LinkedList
{
protected:
	struct listNode {
		listNode *next;
		T val;
	};

	listNode* head;
	listNode* tail;
	int s;

	listNode *traverse(int index);

public:
	LinkedList();

	void add(T ele);
	void addAt(T ele, int index);
	T get(int index);
	bool erase(T ele);
	void eraseAt(int index);
	void eraseAll(T ele);
	int size();
	listNode *getHead();
	listNode *getTail();
};
#endif
