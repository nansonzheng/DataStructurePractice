#include "pch.h"
#include "DynArray.cpp"

template <typename T>
class Heap {
private:
	DynArray<T> heap;
	int s;

	void bubbleUp(int index) {
		if (index <= 0)
			return;
		int parentInd = (index - (index % 2)) / 2;
		if (heap[parentInd] < heap[index]) {
			T temp = heap[parentInd];
			heap[parentInd] = heap[index];
			head[index] = temp;
			bubbleUp(parentInd);
		}
	}

public:
	Heap() : heap(DynArray<T>(10)), s(0) {}
	Heap(int size) : heap(DynArray<T>(size)), s(0) {}

	void add(T ele) {
		heap.add(ele);
		bubbleUp(s);
		s++;
	}

};