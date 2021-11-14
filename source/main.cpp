#include <cstdio>

#include "tree/tree.h"

int main() {
	printf("We in\n");
	avl_tree::AVLTree our_tree(10);

	printf("we create\n");
	our_tree.insert(20);
	our_tree.insert(5);
	our_tree.insert(3);
	our_tree.insert(6);
	our_tree.insert(2);
	our_tree.insert(1);

	our_tree.insert(7);
	//our_tree.dump();
	our_tree.insert(23);
	//our_tree.dump();
	our_tree.insert(4);
	//our_tree.dump();
	our_tree.insert(18);
	//our_tree.dump();
	our_tree.insert(13);
	//our_tree.dump();
	our_tree.insert(58);
	//our_tree.dump();
	our_tree.insert(8);
	//our_tree.dump(); 
	our_tree.insert(16);
	//our_tree.dump();
	our_tree.insert(99);
	//our_tree.dump();
	our_tree.insert(87);
	//our_tree.dump();
	our_tree.insert(32);
	//our_tree.dump();
	our_tree.insert(19);
	//our_tree.dump();
	our_tree.insert(11);
	//our_tree.dump();
	our_tree.insert(33);
	//our_tree.dump();
	our_tree.insert(43);
	//our_tree.dump(); 
	our_tree.insert(37);
	//our_tree.dump();
	our_tree.insert(26);
	//our_tree.dump();
	our_tree.insert(42);
	//our_tree.dump();
	our_tree.insert(9);
	printf("All insert do\n");
	our_tree.dump();
}
