// DataStructurePractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "LinkedList.h"
#include "LinkedList.cpp"
#include "DynArray.cpp"
#include "CircularList.cpp"
#include "RedBlackTree.cpp"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Hello World!\nTesting linked list" << std::endl; 
	LinkedList<int> *ll = new LinkedList<int>();

	ll->add(1);
	ll->add(2);
	ll->addAt(3, 0);
	ll->addAt(4, 1);
	ll->erase(3);
	ll->addAt(5, 2);
	ll->add(6);
	ll->add(5);
	ll->eraseAt(1);
	ll->eraseAll(5);
	std::cout << ll->get(0) << ll->get(1) << ll->get(2) << std::endl;
	std::cout << "final size: " << ll->size() << "; final head: " << ll->getHead()->val << "; final tail: " << ll->getTail()->val << std::endl;
	delete ll;

	std::cout << "Testing dynamic array" << std::endl;

	DynArray<int> *da = new DynArray<int>(5);
	da->add(1);
	da->add(2);
	da->add(3);
	da->add(4);
	(*da)[2] = 5;
	da->eraseAt(1);
	da->add(6);
	da->add(7);
	da->add(8);
	for (auto it = da->begin(); it != da->end(); it++) {
		std::cout << *it;
	}
	std::cout << std::endl << "final size " << da->size() << "; final capacity " << da->capacity() << std::endl;
	delete da;

	CircularList<int> *cl = new CircularList<int>();
	cl->add(1);
	cl->add(2);
	cl->add(3);
	cl->addAt(4, 1);
	cl->erase(3);
	cl->eraseAt(0);
	auto cl_it = cl->begin();
	do {
		std::cout << *cl_it;
	} while (cl_it++ != cl->begin());

	std::cout << std::endl << "ok" << std::endl;
	delete cl;

	std::cout << "Testing Red-Black tree" << std::endl;

	RedBlackTree<int> *rb = new RedBlackTree<int>();
	rb->add(0);
	rb->add(1);
	rb->add(2);
	rb->add(14);
	rb->add(13);
	rb->add(12);
	rb->add(3);
	rb->add(4);
	rb->add(5);
	rb->add(6);
	rb->add(7);
	rb->erase(4);
	rb->printAll();
	rb->erase(5);
	rb->add(11);
	rb->add(10);
	rb->add(9);
	rb->add(8);
	rb->erase(0);
	rb->printAll();
	std::cout << std::endl << "Final size: " << rb->size() << std::endl;

	delete rb;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
