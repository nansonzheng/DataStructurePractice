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

	Node *getSibling(Node *node) {
		Node *parent = node->parent;
		if (parent == nullptr)
			return nullptr;

		return parent->left == node ? parent->right : parent->left;
	}

	Node *getUncle(Node *node) {
		return node->parent == nullptr ? nullptr : getSibling(node->parent);
	}

	void rotateLeft(Node *node) {
		Node *rotateInto = node->right;
		Node *parent = node->parent;
		if (rotateInto == nullptr) {
			throw "Bad rotateLeft call";
			return;
		}

		node->right = rotateInto->left;
		rotateInto->left = node;
		node->parent = rotateInto;
		if (node->right != nullptr)
			node->right->parent = node;

		if (parent != nullptr) {
			if (parent->left == node) {
				parent->left = rotateInto;
			}
			else {
				parent->right = rotateInto;
			}
		}
		// parent nullptr => node was root
		else
			root = rotateInto;

		rotateInto->parent = parent;
	}

	void rotateRight(Node *node) {
		Node *rotateInto = node->left;
		Node *parent = node->parent;
		if (rotateInto == nullptr) {
			throw "Bad rotateRight call";
			return;
		}

		node->left = rotateInto->right;
		rotateInto->right = node;
		node->parent = rotateInto;
		if (node->left != nullptr)
			node->left->parent = node;

		if (parent != nullptr) {
			if (parent->left == node) {
				parent->left = rotateInto;
			}
			else {
				parent->right = rotateInto;
			}
		}
		// parent nullptr => node was root
		else
			root = rotateInto;

		rotateInto->parent = parent;
	}

	void insert(Node *child, Node *parent) {
		// Find appropriate lowermost node and insert
		while (parent != nullptr) {
			if (ele < parent->val) {
				if (parent->left != nullptr)
					parent == parent->left;
				else {
					parent->left = child;
					break;
				}
			}
			else {
				if (parent->right != nullptr)
					parent = parent->right;
				else {
					parent->right = child;
					break;
				}
			}
		}

		child->parent = parent;
		// nullptr parent => nullptr root => empty tree
		if (parent == nullptr) {
			root = child;
		}

		// Insert-specific balancing act
		balanceInsert(child);
		return;
	}

	void balanceInsert(Node *node) {
		Node *parent = node->parent;
		// case 1: node is root
		if (parent == nullptr) {
			node->black = true;
			return;
		}
		// case 2: parent is black
		else if (parent->black) {
			return;
		}
		else {
			Node *uncle = getUncle(node);
			Node *grand = parent->parent;
			// case 3: parent and uncle are both red
			if (uncle != nullptr && !uncle->black) {
				parent->black = getUncle(node)->black = true;
				grand->black = false;
				balanceInsert(grand);
				return;
			}
			// case 4: parent is red but uncle is black
			else {
				// step 1: rotate out the inner child node if exists, and switch node to new child
				if (node == parent->right && parent == grand->left) {
					rotateLeft(parent);
					node = node->left;

					parent = node->parent;
					grand = parent->parent;
				}
				else if (node == parent->left && parent == grand->right) {
					rotateRight(parent);
					node = node->right;

					parent = node->parent;
					grand = parent->parent;
				}
				if (node == parent->left)
					rotateRight(grand);
				else
					rotateLeft(grand);

				parent->black = true;
				grand->black = false;
			}
		}
	}

	void eraseSpecial(Node *node) {
		Node *child = (node->right == nullptr) ? node->left : node->right;

		child->parent = node->parent;
		if (node->parent != nullptr)
			if (node == node->parent->left)
				node->parent->left = child;
			else
				node->parent->right = child;
		
		if (node->black) {
			if (!child->black) 
				child->black = true;
			else 
				eraseRebalance(node);
		}
		delete node;
	}

	void eraseRebalance(Node *node) {
		Node *parent = node->parent;
		if (parent != nullptr) {
			Node *sibling = getSibling(node);

			// case 2: sibling is red
			// proceed to case 3 regardless
			if (!sibling->black) {
				parent->black = false;
				sibling->black = true;
				if (node == parent->left)
					rotateLeft(parent);
				else
					rotateRight(parent);
			}
			// case 3: parent, sibling and sibling's children are all black
			if (parent->black 
				&& sibling->black 
				&& (sibling->left == nullptr || sibling->left->black)
				&& (sibling->right == nullptr || sibling->right->black)) {
				sibling->black = false;
				eraseRebalance(parent);
			}
			// case 4: parent is red, sibling and its children are black
			else if (!parent->black
				&& sibling->black
				&& (sibling->left == nullptr || sibling->left->black)
				&& (sibling->right == nullptr || sibling->right->black)) {
				sibling->black = false;
				parent->black = true;
			}
			// case 5: sibling's left child is red, others are black. Node to delete is left of parent
			// proceed to case 6 regardless
			else {
				// redundant check due to case 2 but just in case lel
				if (sibling->black) {
					if (node == parent->left
						&& (sibling->right == nullptr || sibling->right->black)
						&& (sibling->left != nullptr && !sibling->left->black)) {
						sibling->black = false;
						sibling->left->black = true;
						rotateRight(sibling);
					}
					else if (node == parent->right
						&& (sibling->left == nullptr || sibling->left->black)
						&& (sibling->right != nullptr && !sibling->right->black)) {
						sibling->black = false;
						sibling->right->black = true;
						rotateLeft(sibling);
					}

					// case 6: sibling is black, sibling right child is red, node is left child of parent
					sibling->black = parent->black;
					node->parent->black = true;
					if (node == parent->left) {
						if (sibling->right != nullptr)
							sibling->right->black = true;
						rotateLeft(parent);
					}
					else {
						if (sibling->left != nullptr)
							sibling->left->black = true;
						rotateRight(parent);
					}
				}
			}
		}
	}

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
		
		insert(node, root);

		return node;
	}

	void erase(T ele) {
		Node *node = root;

		while (node != nullptr) {
			if (ele == node->val)
				break;
			else if (ele < node->val)
				node = node->left;
			else node = node->right;
		}
		if (node == nullptr) {
			throw "Element with specified value not found";
			return;
		}

		// Trivial case: leaf node (AKA 2 leaf children (nil))
		if (node->left == nullptr && node->right == nullptr) {
			Node *parent = node->parent;
			if (parent == nullptr)
				root = nullptr;
			else {
				if (node == parent->left)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			}

			delete node;
			return;
		}
		// Case: max 1 null child
		else
			eraseSpecial(node);
	}
};