#include "../../containers/rbtree.hpp"

int main()
{
	ft::rbtree<int> bst;
	bst.insert(55);
	bst.insert(40);
	bst.insert(65);
	bst.insert(60);
	bst.insert(75);
	bst.insert(57);

	bst.printTree();
	std::cout << std::endl
			  << "After deleting" << std::endl;
	bst.deleteNode(40);
	bst.printTree();
}
