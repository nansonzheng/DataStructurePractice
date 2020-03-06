#include "pch.h"

template <typename T>
class RedBlackTree {
private:
	struct Node {
		Node *left;
		Node *right;
		Node *parent;
		T val;
		bool black;
	};

	Node *root;

public:
	RedBlackTree() : root(nullptr) {}

	Node *add(T ele) {
		Node *node = new Node{
			nullptr,
			nullptr,
			nullptr,
			ele,
			false
		};
		
		Node *parent = root;
		while (parent != root) {

		}
	}
};