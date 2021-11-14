#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "tree.h"

#define MAX_NAME_SIZE 75

namespace avl_tree {

	void AVLTree::dump() {

		FILE* potok = FileOpen("Enter file name, where will be dump graph\n", "w");
		if (potok == nullptr) return;

		fprintf(potok, "digraph G {\n");
		print_graph(top_, potok);
		fprintf(potok, "}\n");

		fclose(potok);
	}

	void print_graph(Node* node, FILE* potok) {// So slooow
		printf("we print %d ", node->key_);
		if (node->left_ != nullptr) printf("left is %d, ", node->left_->key_);
		if (node->right_ != nullptr) printf("right is %d, ", node->right_->key_);
		if (node->parent_ != nullptr) printf("parent is %d, ", node->parent_->key_);
		printf("\n");

		if (node->left_ != nullptr) {
			fprintf(potok, "\"%d", node->key_);
			fprintf(potok, "\" -> \"%d", node->left_->key_);
			fprintf(potok, "\";\n");

			print_graph(node->left_, potok);
		}

		if (node->right_ != nullptr) {
			fprintf(potok, "\"%d", node->key_);
			fprintf(potok, "\" -> \"%d", node->right_->key_);
			fprintf(potok, "\";\n");

			print_graph(node->right_, potok);
		}

		if (node->parent_ != nullptr) {
			fprintf(potok, "\"%d", node->key_);
			fprintf(potok, "\" -> \"%d", node->parent_->key_);
			fprintf(potok, "\";\n");
		}
	}

	FILE* FileOpen(const char* text, const char* mode) {

		printf(text);
		char* answer = (char*)calloc(MAX_NAME_SIZE, sizeof(char));

		fseek(stdin, 0, SEEK_END);
		std::cin.getline(answer, MAX_NAME_SIZE, '\n');

		FILE* potok = fopen(answer, mode);
		free(answer);
		return potok;
	}

}