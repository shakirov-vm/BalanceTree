#include <cstdio>
#include <iostream>
#include "tree/tree.h"

int main() {
	printf("We in\n\n");

	avl_tree::AVLTree our_tree(4);

	printf("we create\n");

	/*our_tree.insert(5);
	our_tree.insert(4);
	our_tree.insert(3);
	our_tree.insert(2);
	our_tree.insert(1);*/
	our_tree.insert(2);
	our_tree.insert(1);
	our_tree.insert(3);
	our_tree.insert(6);
	our_tree.insert(5);
	our_tree.insert(7);
	//printf("%ld, %d\n", our_tree.top_->left_->key_, our_tree.top_->right_->left_->key_);

	our_tree.dump();

}
