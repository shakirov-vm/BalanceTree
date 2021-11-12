#include <cstdio>

#include "tree/tree.h"

int main() {
	avl_tree::AVLTree our_tree(100);

	/*printf("we create\n");
	if (!our_tree.insert(5)) printf("Dont push 5\n");
	if (!our_tree.insert(7)) printf("Dont push 7\n");
	if (!our_tree.insert(12)) printf("Dont push 12\n");
	if (!our_tree.insert(1)) printf("Dont push 1\n");
	if (!our_tree.insert(4)) printf("Dont push 4\n");
	if (!our_tree.insert(18)) printf("Dont push 18\n");
	if (!our_tree.insert(13)) printf("Dont push 13\n");
	if (!our_tree.insert(58)) printf("Dont push 58\n");
	if (!our_tree.insert(8)) printf("Dont push 8\n");
	if (!our_tree.insert(2)) printf("Dont push 2\n");
	if (!our_tree.insert(23)) printf("Dont push 23\n");
	if (!our_tree.insert(42)) printf("Dont push 42\n");
	if (!our_tree.insert(9)) printf("Dont push 9\n");
	printf("All insert do\n");
	our_tree.dump();*/

	printf("we create\n");
	our_tree.insert(our_tree.top_, 5);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 7);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 23);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 1);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 4);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 18);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 13);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 58);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 8);
	//our_tree.dump(); 
	our_tree.insert(our_tree.top_, 2);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 23);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 42);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 27);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 16);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 99);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 87);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 32);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 19);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 11);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 33);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 43);
	//our_tree.dump(); 
	our_tree.insert(our_tree.top_, 37);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 26);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 42);
	//our_tree.dump();
	our_tree.insert(our_tree.top_, 9);
	printf("All insert do\n");
	our_tree.dump();
}

/*
void recPreOrder(Node* node) {
	printf("key: %d, left - %p, right - %p\n", node->key_, node->left_, node->right_);
	if (node->left_ != nullptr) recPreOrder(node->left_);
	if (node->right_ != nullptr) recPreOrder(node->right_);
}
*/