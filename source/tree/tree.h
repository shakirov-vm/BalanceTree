#include <fstream>

#pragma once

namespace avl_tree {

	using key_t = int;

	struct Node {
		key_t key_;
		Node* left_;
		Node* right_;
		Node* parent_;

		size_t left_size_;
		int height_;

		Node(key_t key = 0, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, size_t left_size = 0, int height = 1) :
			key_(key),
			left_(left),
			right_(right),
			parent_(parent),
			left_size_(left_size),
			height_(height) {}

		void dump() {
			if (this == nullptr) {
				printf("node is nullptr\n");
				return;
			}
			std::cout << "node is " << key_ << ", ";
			if (left_ != nullptr) std::cout << "left is " << left_->key_ << ", ";
			if (right_ != nullptr) std::cout << "right is " << right_->key_ << ", ";
			if (parent_ != nullptr) std::cout << "parent is " << parent_->key_ << ", ";
			std::cout << std::endl;
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

		AVLTree() : top_(nullptr) {}
		AVLTree(key_t key) {
			top_ = new Node(key);
		}
		AVLTree(const AVLTree& other);
		AVLTree(AVLTree&& tmp);
		AVLTree& operator= (const AVLTree& other);
		AVLTree& operator= (AVLTree&& tmp);
		~AVLTree();

		void insert(key_t key);
		key_t find_k_ordinal_stat(size_t k) const;
		size_t find_num_less_that_k(size_t k) const;
		void dump();

	};

	void print_graph(Node* node, std::ofstream& potok);
}

