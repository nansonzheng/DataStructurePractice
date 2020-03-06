#include "pch.h"

template <typename T>
class DynArray {
private:
	T *arr;
	int s, cap;

	typedef T* iterator;
	typedef const T* const_iterator;
	
	iterator _it;
	const_iterator _cit;

	void expand() {
		T* newArr = new T[cap * 2];
		for (int i = 0; i < s; i++) {
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
		cap = cap * 2;
	}

public:

	DynArray(int size) : arr(new T[size]), s(0), cap(size){
	}

	~DynArray() {
		delete[] arr;
	}

	T& operator[](int index) {
		return arr[index];
	}

	const T& operator[](int index) const {
		return arr[index];
	}

	iterator begin() const {
		return &arr[0];
	}
	iterator end() const {
		return &arr[s];
	}

	T operator*() {
		return *_it;
	}

	T* operator->() {
		return _it;
	}

	iterator operator++() {
		iterator i = *this;
		_it++;
		return i;
	}

	iterator operator++(int i) {
		_it++;
		return *this;
	}

	iterator operator!=(const iterator& other) {
		return _it != other;
	}

	iterator operator==(const iterator& other) {
		return _it == other;
	}

	void add(T ele) {
		if (s == cap)
			expand();

		arr[s++] = ele;
	}

	void erase(T ele) {
		auto it = begin();
		for (; it != end() && *it != ele; it++);
		if (it == end())
			return;
		it;
		for (auto it2 = it + 1; it2 != end(); it2++) {
			*it = *it2;
			it++;
		}
		s--;
		return;
	}

	void eraseAt(int index) {
		auto it = begin() + index;
		for (auto it2 = it + 1; it2 != end(); it2++) {
			*it = *it2;
			it++;
		}
		s--;
		return;
	}

	T& at(int index) {
		return arr[index];
	}

	int size() {
		return s;
	}

	int capacity() {
		return cap;
	}
};