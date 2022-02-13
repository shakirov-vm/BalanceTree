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
	our_tree.insert(15);
	our_tree.insert(8);
	our_tree.insert(12);
	our_tree.insert(3);
	our_tree.insert(6);
	our_tree.insert(14);
	our_tree.insert(5);
	our_tree.insert(7);
	//printf("%ld, %d\n", our_tree.top_->left_->key_, our_tree.top_->right_->left_->key_);

	/*our_tree.dump();
	std::cout << "Before copy" << std::endl;
	avl_tree::AVLTree copy_tree(our_tree);
	copy_tree.dump();*/
our_tree.dump();
	size_t a = our_tree.find_k_ordinal_stat(3);
	std::cout << "third it is " << a << std::endl;

	a = our_tree.find_k_ordinal_stat(7);
	std::cout << "seventh it is " << a << std::endl;

	a = our_tree.find_k_ordinal_stat(10);
	std::cout << "tenth it is " << a << std::endl;

	a = our_tree.find_k_ordinal_stat(13);
	std::cout << "thirteenth it is " << a << std::endl;

	a = our_tree.find_num_less_that_k(6);
	std::cout << "less than 6 is " << a << std::endl;

	a = our_tree.find_num_less_that_k(11);
	std::cout << "less than 11 is " << a << std::endl;

	a = our_tree.find_num_less_that_k(13);
	std::cout << "less than 13 is " << a << std::endl;

	a = our_tree.find_num_less_that_k(111);
	std::cout << "less than 111 is " << a << std::endl;

}
