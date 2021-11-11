#include <cstdio>

#include "tree/tree.h"

int main() {
	avl_tree::AVLTree our_tree(6);
	//our_tree.dump();
	printf("we create\n");
	if (our_tree.insert(5)) printf("Dont push 5\n");
//	our_tree.dump();
	if (our_tree.insert(7)) printf("Dont push 7\n");
	if (our_tree.insert(12)) printf("Dont push 12\n");
	if (our_tree.insert(1)) printf("Dont push 1\n");
	if (our_tree.insert(4)) printf("Dont push 4\n");
	if (our_tree.insert(18)) printf("Dont push 18\n");
	if (our_tree.insert(13)) printf("Dont push 13\n");
	if (our_tree.insert(58)) printf("Dont push 58\n");
	if (our_tree.insert(8)) printf("Dont push 8\n");
	if (our_tree.insert(2)) printf("Dont push 2\n");
	if (our_tree.insert(23)) printf("Dont push 23\n");
	if (our_tree.insert(42)) printf("Dont push 42\n");
	if (our_tree.insert(9)) printf("Dont push 9\n");
	printf("All insert do\n");
	our_tree.dump();
}