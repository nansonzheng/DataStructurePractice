#include "pch.h"
#include <vector>
#include <string>

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
	int s;

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
			if (child->val < parent->val) {
				if (parent->left != nullptr)
					parent = parent->left;
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

	// Erases node to be replaced
	void eraseSpecial(Node *node) {
		Node *child = (node->right == nullptr) ? node->left : node->right;
		Node *parent = node->parent;

		// link child and parent
		if (child != nullptr) {
			child->parent = parent;
			if (parent != nullptr) {
				if (node == parent->left)
					parent->left = child;
				else
					parent->right = child;
				root = node;
			}
			if (node->black) {
				if (!child->black)
					child->black = true;
				else
					eraseRebalance(child);
			}
		}
		// "leaf" node - only null children
		else {
			eraseRebalance(node);
			// node cannot be root with no children because 
			//it's checked before entering this function
			if (node == parent->left) 
				parent->left = nullptr;
			else
				parent->right = nullptr;
		}
		
		delete node;
	}

	void eraseRebalance(Node *node) {
		Node *parent = node->parent;
		// case 1
		if (parent == nullptr)
			return;
		
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
		// case 5: sibling's inner child is red, others are black
		// proceed to case 6 regardless
		else {
			// redundant check due to case 2 but just in case lel
			if (sibling->black) {
				// checks for inner child and rotate to make outer child red
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

				// case 6: sibling is black, sibling's outer child is red
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

	void print(Node *node) {
		std::cout << "Node" << node->val << " " << (node->black? "BLACK" : "RED")
			<< " parent: " << ((node->parent == nullptr)? "NULL" : std::to_string(node->parent->val)) <<std::endl;
	}

public:
	RedBlackTree() : root(nullptr), s(0) {}

	Node *add(T ele) {
		Node *node = new Node{
			nullptr,
			nullptr,
			nullptr,
			ele,
			false
		};
		
		insert(node, root);
		s++;
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

		// Find successor/predecessor if any
		Node *replace = nullptr;
		if (node->right != nullptr) {
			replace = node->right;
			while (replace->left != nullptr)
				replace = replace->left;
		}
		else if (node->left != nullptr) {
			replace = node->left;
			while (replace->right != nullptr) {
				replace = replace->right;
			}
		}
		
		// Replace node if necessary
		Node *parent = node->parent;
		if (replace != nullptr) {
			node->val = replace->val;
			eraseSpecial(replace);
		}
		// node has no children
		else {
			if (node == root) {
				root = nullptr;
				delete node;
				return;
			}
			else
				eraseSpecial(node);
		}
		s--;
	}

	bool contains(T ele) {
		Node *node = root;
		while (node != nullptr && node->val != ele) {
			if (ele < node->val)
				node = node->left;
			else
				node = node->right;
		}
		return node != nullptr;
	}

	std::vector<T> inOrder() {
		return inOrder(root);
	}

	std::vector<T> inOrder(Node *node) {
		std::vector<T> res = std::vector<T>(), temp;
		if (node->left != nullptr) {
			temp = inOrder(node->left);
			res = temp;
		}
		res.emplace_back(node->val);
		if (node->right != nullptr) {
			temp = inOrder(node->right);
			res.insert(res.end(), temp.begin(), temp.end());
		}
		return res;
	}

	int size() {
		return s;
	}

	void printAll() {
		if (root != nullptr)
			printAll(root);
	}

	void printAll(Node *node) {
		if (node->left != nullptr)
			printAll(node->left);
		print(node);
		if (node->right != nullptr)
			printAll(node->right);
	}

	Node *getRoot() {
		return root;
	}
};