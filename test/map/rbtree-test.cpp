#include "../../containers/rbtree.hpp"
#include "../../containers/rbtree_iterator.hpp"
#include <iostream>
#include <map>

int main()
{
	ft::rbtree<std::pair<char, int> > bst;
	bst.insertNode(std::pair<char, int>('a', 1));
	bst.insertNode(std::pair<char, int>('b', 1));
	bst.insertNode(std::pair<char, int>('c', 1));
	bst.insertNode(std::pair<char, int>('d', 1));
	/*
	bst.insertNode(55);
	bst.insertNode(40);
	bst.insertNode(65);
	bst.insertNode(60);
	bst.insertNode(75);
	bst.insertNode(57);
	*/

	ft::rbtree_iterator<std::pair<char, int> > it(bst.getRoot());
	it++;
	// it--;

	std::cout << it->first << std::endl;
}
