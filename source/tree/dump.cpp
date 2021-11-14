#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "tree.h"

#define MAX_NAME_SIZE 75

namespace avl_tree {

	void AVLTree::dump() {

		printf("Enter file name, where will be dump graph\n");
		char answer[MAX_NAME_SIZE] = {};

		fseek(stdin, 0, SEEK_END);
		std::cin.getline(answer, MAX_NAME_SIZE, '\n');

		std::ofstream potok;
		potok.open(answer);

		if (!potok.is_open()) return;

		potok << "digraph G {\n";
		print_graph(top_, potok);
		potok << "}\n";

		potok.close();
	}

	void print_graph(Node* node, std::ofstream& potok) {// So slooow
	
		if (node->left_ != nullptr) {
			potok << "\"" << node->key_;
			potok << "\" -> \"" << node->left_->key_;
			potok << "\";\n";

			print_graph(node->left_, potok);
		}

		if (node->right_ != nullptr) {
			potok << "\"" << node->key_;
			potok << "\" -> \"" << node->right_->key_;
			potok << "\";\n";

			print_graph(node->right_, potok);
		}

		if (node->parent_ != nullptr) {
			potok << "\"" << node->key_;
			potok << "\" -> \"" << node->parent_->key_;
			potok << "\";\n";
		}
	}

}