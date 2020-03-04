#pragma once
#include "pch.h"
#ifndef DYNARRAY_H
#define DYNARRAY_H

template <typename T>
class DynArray {
private:
	T *arr;
	int s, cap;
	void expand();
	void shrink();

public:
	DynArray(int size);

	T& operator[](int);
	const T& operator[](int) const;

	void add(T ele);
	void addAt(T ele, int index);
	void erase(T ele);
	void eraseAt(int index);

	T& at(int index);
	int size();
};

#endif