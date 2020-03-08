#include "pch.h"

template <typename T>
class Heap {
private:
	struct Node {
		Node *left;
		Node *right;
		T val;
	};

	Node *root;
	int s;

public:
	Heap(): root(nullptr), s(0){}

	void add(T ele) {

	}
};