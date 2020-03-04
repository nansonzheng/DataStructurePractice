#include "pch.h"
#include "DynArray.h"

template <typename T>
DynArray<T>::DynArray(int initSize) : s(0), cap(initSize) {
	arr = new T[initSize];
}

template <typename T>
void DynArray<T>::expand() {
	T[] newArr = new T[cap * 2];
	memmove(newArr, arr, sizeof(T) * cap);
	delete[] arr;
	arr = newArr;
	cap = cap * 2;
}

template <typename T>
void DynArray<T>::shrink() {
	T[] newArr = new T[cap / 2];
	memmove(newArr, arr, sizeof(T) * cap / 2);
	delete[] arr;
	arr = newArr;
	cap = cap / 2;
}

template <typename T>
T& DynArray<T>::operator[] (int index) {
	return arr[index];
}

template <typename T>
const T& DynArray<T>::operator[] (int index) const {
	return arr[index];
}

template <typename T>
void add(T ele) {

}