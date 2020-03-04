#pragma once
#include "pch.h"
#ifndef DYNARRAY_H
#define DYNARRAY_H

template <typename T>
class DynArray {
private:
	T *arr;
	int s, cap;
	void resize();

public:
	DynArray(int size);

	T& operator[](int);
	const T& operator[](int) const;

	T& at(int index);
	int size();
};

#endif