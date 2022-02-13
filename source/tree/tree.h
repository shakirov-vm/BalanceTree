#include <fstream>

#pragma once

namespace avl_tree {

	using key_t = int;

	struct Node {
		key_t key_;
		Node* left_;
		Node* right_;
		Node* parent_;

		int left_size_;
		int right_size_;

		int height_;

		Node(key_t key = 0, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, int left_size = 0, int right_size = 0, int height = 1) :
			key_(key),
			left_(left),
			right_(right),
			parent_(parent),
			left_size_(left_size),
			right_size_(right_size),
			height_(height) {}

		void dump() {
			if (this == nullptr) {
				printf("node is nullptr\n");
				return;
			}
			printf("node is %d ", key_);
			if (left_ != nullptr) printf("left is %d, ", left_->key_);
			if (right_ != nullptr) printf("right is %d, ", right_->key_);
			if (parent_ != nullptr) printf("parent is %d, ", parent_->key_);
			printf("\n");
		}

		int balance_factor();
		void fix_height();
		int height();
		Node* balance();
		Node* left_rotate();
		Node* right_rotate();

	};

	class AVLTree {
		Node* top_;

	public:

		AVLTree(key_t key = 0) {
			top_ = new Node(key);
		}
		~AVLTree();
		AVLTree(const AVLTree& other);
		bool insert(key_t key);
		void dump();

	};

	void print_graph(Node* node, std::ofstream& potok);

}

