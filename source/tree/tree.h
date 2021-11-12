#pragma once

namespace avl_tree {

	using key_t = int;

	struct Node {
		key_t key_;
		int height_;

		Node* left_;
		Node* right_;
		Node* parent_;

		int left_size_;
		int right_size_;

		// Не делаем конструктора по умолчанию, так как операции set не планируется
		Node(key_t key, int height = 1, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) :
			key_(key),
			height_(height),
			left_(left),
			right_(right),
			parent_(parent),
			left_size_(0),
			right_size_(0) {}

		int balance_factor();
		void fixheight();
		int height();

		//big_left_rotate();
		//big_right_rotate();
	};

	struct AVLTree {
		Node* top_;

		Node* balance(Node* node);
		Node* left_rotate(Node* node);
		Node* right_rotate(Node* node);

	public:

		AVLTree(key_t key = 0) {
			top_ = new Node(key);
		}
		//bool insert(key_t key);
		Node* insert(Node* node, key_t key);
		void dump();

	};


	FILE* FileOpen(const char* text, const char* mode);
	void print_graph(Node* node, FILE* potok);

}
